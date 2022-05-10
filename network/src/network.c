#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "encoder.h"
#include "classifier.h"
#include "assert.h"
#include "helpful.h"

#define N_CYCLES 2000

struct Network_T {
    struct shape2_t input_shape;
    struct shape2_t label_shape;
    int n_filters;
    int n_layers;
    Encoder_T encoder;
    Layer_T last_layer;
    Classifier_T classifier;
    Filter_T *filters;
    Layer_T *layers;
    float MSE;
};

Network_T Network_new(shape2_t input_shape, shape2_t label_shape)
{
    Network_T net = malloc(sizeof(struct Network_T));

    net->input_shape = *input_shape;
    net->label_shape = *label_shape;

    net->encoder    = Encoder_new(input_shape);
    net->classifier = Classifier_new(label_shape);
    net->last_layer = Layer_new(label_shape, input_shape);

    net->n_layers  = 0;
    net->n_filters = 0;

    net->layers  = NULL;
    net->filters = NULL;

    return net;
}

void Network_free(Network_T *net)
{
    for (int i = 0; i < (*net)->n_filters; i++)
        Filter_free(&(*net)->filters[i]);

    for (int i = 0; i < (*net)->n_layers; i++)
        Layer_free(&(*net)->layers[i]);

    Layer_free(&(*net)->last_layer);
    Classifier_free(&(*net)->classifier);
    Encoder_free(&(*net)->encoder);

    free((*net)->filters);
    free((*net)->layers);

    free(*net);
    *net = NULL;
}

static void resize_last_layer(Network_T net, shape2_t input_shape);

void Network_add_layer(Network_T net, param_t params)
{
    struct shape2_t shape = {params->x, params->y};

    net->layers = realloc(net->layers, sizeof(Layer_T) * (net->n_layers + 1));
    assert(net->layers);

    /* start with input shape as encoder */
    shape2_t input = Encoder_shape(net->encoder);

    /* if there are filters make it the last one */
    if (net->n_filters != 0)
        input = Filter_shape(net->filters[net->n_filters - 1]);

    /* if there are layers make it the last one */
    if (net->n_layers != 0)
        input = Layer_shape(net->layers[net->n_layers - 1]);

    Layer_T new_layer = Layer_new(&shape, input);
    if (params != NULL)
        Layer_set_params(new_layer, params);
    net->layers[net->n_layers] = new_layer;
    net->n_layers++;

    resize_last_layer(net, &shape);
}

void Network_add_filter(Network_T net, param_t params, int n_filters)
{
    /* filters must come before layers */
    assert(net->n_layers == 0);
    struct shape2_t shape = {params->x, params->y};

    net->filters = realloc(net->filters,
                           sizeof(Filter_T) * (net->n_filters + 1));
    assert(net->layers);

    /* start with input shape as encoder */
    shape2_t input = Encoder_shape(net->encoder);

    /* if there are filters make it the last one */
    if (net->n_filters != 0)
        input = Filter_shape(net->filters[net->n_filters - 1]);

    Filter_T new_filter = Filter_new(&shape, input, n_filters);
    if (params != NULL)
        Filter_set_params(new_filter, params);
    net->filters[net->n_filters] = new_filter;
    net->n_filters++;

    if (net->n_layers == 0) {
        resize_last_layer(net, &shape);
    }
}

static inline void propagate_spikes(Network_T net);
static inline void log_data(Network_T net, Log_T log);

int Network_feed(Network_T net, float2_t input, float2_t label, Log_T log)
{
    int decision, n_cycles = N_CYCLES;

    Encoder_set_current(net->encoder, input->data);

    if (log == NULL) {
        for (int i = 0; i < n_cycles; i++) {
            propagate_spikes(net);
        }
    } else {
        for (int i = 0; i < n_cycles; i++) {
            log->time = log->input_index * n_cycles + i;
            propagate_spikes(net);
            log_data(net, log);
        }
    }

    decision = Classifier_decision(net->classifier);
    net->MSE = Classifier_MSE(net->classifier, label);
    // Classifier_print_summary(net->classifier);
    Classifier_reset(net->classifier);

    return decision;
}

static inline void propagate_spikes(Network_T net)
{
    int n_filters = net->n_filters;
    int n_layers  = net->n_layers;
    bit2_t spikes = Encoder_spikes(net->encoder);

    // printf("\n======================================\n");

    // fprintarrb(spikes->data, spikes->x * spikes->y, stdout);

    for (int i = 0; i < n_filters; i++) {
        spikes = Filter_feed(net->filters[i], spikes);
        // fprintarrb(spikes->data, spikes->x * spikes->y, stdout);
    }

    for (int i = 0; i < n_layers; i++) {
        spikes = Layer_feed(net->layers[i], spikes);
        // fprintarrb(spikes->data, spikes->x * spikes->y, stdout);
        // fprintarrf(net->layers[i]->voltages->data, net->layers[i]->shape.x * net->layers[i]->shape.y, stdout);
    }

    spikes = Layer_feed(net->last_layer, spikes);
    // fprintarrb(spikes->data, spikes->x * spikes->y, stdout);
    // fprintarrf(net->last_layer->voltages->data, net->last_layer->shape.x * net->last_layer->shape.y, stdout);

    Classifier_feed(net->classifier, spikes);


    // printf("======================================\n\n");
}

static inline void log_data(Network_T net, Log_T log)
{
    int n_filters = net->n_filters;
    int n_layers  = net->n_layers;

    for (int i = 0; i < n_filters; i++)
        Log_filter(log, net->filters[i], (i + 1) * n_filters + (i + 1));

    for (int i = 0; i < n_layers; i++)
        Log_layer(log, net->layers[i], (i + 1));

    Log_layer(log, net->last_layer, (n_layers + 1));
}

static void resize_last_layer(Network_T net, shape2_t input_shape)
{
    Layer_free(&net->last_layer);
    net->last_layer = Layer_new(&net->label_shape, input_shape);
}

Layer_T Network_layer_at(Network_T net, int i)
{
    assert(i >= 0 && i < net->n_layers);
    return net->layers[i];
}

Filter_T Network_filter_at(Network_T net, int i)
{
    assert(i >= 0 && i < net->n_filters);
    return net->filters[i];
}

void Network_print_topography(Network_T net)
{
    int n_filters = net->n_filters;
    int n_layers  = net->n_layers;
    fprintshp("\nThe input shape is ", &net->input_shape, stderr);
    for (int i = 0; i < n_filters; i++) {
        fprintf(stderr, "Filter %i has %i layers with ",
                        i, net->filters[i]->n_filters);
        fprintshp("shape ", Filter_shape(net->filters[i]), stderr);
    }
    for (int i = 0; i < n_layers; i++) {
        fprintf(stderr, "Layer %i has ", i);
        fprintshp("shape ", Layer_shape(net->layers[i]), stderr);
    }
    fprintf(stderr, "Layer %i has ", n_layers);
    fprintshp("shape ", Layer_shape(net->last_layer), stderr);
    fprintshp("The output shape is ", &net->label_shape, stderr);
    fprintf(stderr, "\n");
}

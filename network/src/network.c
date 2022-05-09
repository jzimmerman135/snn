#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "filter.h"
#include "encoder.h"
#include "classifier.h"
#include "assert.h"
#include "helpful.h"

#define N_CYCLES 1000

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

void Network_add_layer(Network_T net, shape2_t shape, param_t params)
{
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

    Layer_T new_layer = Layer_new(shape, input);
    if (params != NULL)
        Layer_set_params(new_layer, params);
    net->layers[net->n_layers] = new_layer;
    net->n_layers++;

    resize_last_layer(net, shape);
}

void Network_add_filter(Network_T net, shape2_t shape, int n_filters,
                        param_t params)
{
    /* filters must come before layers */
    assert(net->n_layers == 0);

    net->filters = realloc(net->filters,
                           sizeof(Filter_T) * (net->n_filters + 1));
    assert(net->layers);

    /* start with input shape as encoder */
    shape2_t input = Encoder_shape(net->encoder);

    /* if there are filters make it the last one */
    if (net->n_filters != 0)
        input = Filter_shape(net->filters[net->n_filters - 1]);

    Filter_T new_filter = Filter_new(shape, input, n_filters);
    if (params != NULL)
        Filter_set_params(new_filter, params);
    net->filters[net->n_filters] = new_filter;
    net->n_filters++;

    if (net->n_layers == 0) {
        resize_last_layer(net, shape);
    }
}

static inline void propagate_spikes(Network_T net);

int Network_feed(Network_T net, float2_t input, float2_t label)
{
    int decision, n_cycles = N_CYCLES;

    Encoder_set_current(net->encoder, input->data);

    for (int i = 0; i < n_cycles; i++)
        propagate_spikes(net);

    decision = Classifier_decision(net->classifier);
    net->MSE = Classifier_MSE(net->classifier, label);
    Classifier_reset(net->classifier);

    return decision;
}

static inline void propagate_spikes(Network_T net)
{
    int n_filters = net->n_filters;
    int n_layers  = net->n_layers;
    bit2_t spikes = Encoder_spikes(net->encoder);

    for (int i = 0; i < n_filters; i++)
        spikes = Filter_feed(net->filters[i], spikes);

    for (int i = 0; i < n_layers; i++)
        spikes = Layer_feed(net->layers[i], spikes);

    spikes = Layer_feed(net->last_layer, spikes);
    Classifier_feed(net->classifier, spikes);
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

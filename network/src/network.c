#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "layer.h"
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


    Classifier_free(&(*net)->classifier);
    Encoder_free(&(*net)->encoder);

    free((*net)->filters);
    free((*net)->layers);

    free(*net);
    *net = NULL;
}

void Network_add_layer(Network_T net, shape2_t shape)
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


    net->layers[net->n_layers] = Layer_new(shape, input);

    net->n_layers++;
}

void Network_add_filter(Network_T net, shape2_t shape, int n_filters)
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

    net->filters[net->n_filters] = Filter_new(shape, input, n_filters);
    net->n_filters++;
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

    Classifier_feed(net->classifier, spikes);
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

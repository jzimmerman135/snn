#include <math.h>
#include "layer.h"
#include "spikemath.h"
#include "helpful.h"
#include <stdio.h>

void Layer_accumulate(Layer_T layer, bit2_t synapses);
void Layer_train(Layer_T layer);

Layer_T Layer_new(shape2_t output_shape, shape2_t input_shape)
{
    struct shape2_t s = *output_shape;
    struct shape2_t in = *input_shape;
    Layer_T layer = malloc(sizeof(struct Layer_T));

    layer->shape = s;
    layer->input_shape = in;

    int n_neurons = layer->shape.x * layer->shape.y;

    layer->weights = malloc(sizeof(float2_t) * n_neurons);
    layer->syn_pre = malloc(sizeof(bit2_t) * n_neurons);

    for (int i = 0; i < n_neurons; i++) {
        layer->weights[i] = float2_new(in.x, in.y);
        layer->syn_pre[i] = bit2_new(in.x, in.y);
    }

    layer->currents      = float2_new(s.x, s.y);
    layer->voltages      = float2_new(s.x, s.y);
    layer->voltages_stdp = float2_new(s.x, s.y);
    layer->inferences    = bit2_new(s.x, s.y);
    layer->stdp_spikes   = bit2_new(s.x, s.y);

    layer->inter_inhibition = NULL;

    /* default hyperparameter values, please set manually */
    layer->threshold     = 10;
    layer->potentiation  = 0.8;
    layer->depression    = 0.1;
    layer->beta          = 0.02;

    fprintshp("ADDED A NEW LAYER! ", &layer->shape, stderr);
    fprintshp("New layer's input has ", &layer->input_shape, stderr);

    return layer;
}


void Layer_free(Layer_T *layer)
{
    int n_neurons = (*layer)->shape.x * (*layer)->shape.y;

    for (int i = 0; i < n_neurons; i++) {
        float2_free(&(*layer)->weights[i]);
        bit2_free(&(*layer)->syn_pre[i]);
    }

    float2_free(&(*layer)->currents);
    float2_free(&(*layer)->voltages);
    float2_free(&(*layer)->voltages_stdp);

    bit2_free(&(*layer)->inferences);
    bit2_free(&(*layer)->stdp_spikes);

    free((*layer)->weights);
    free((*layer)->syn_pre);
    free(*layer);
    *layer = NULL;
}

void Layer_connect_inhibition(Layer_T layer, bit2_t inh_matrix)
{
    layer->inter_inhibition = inh_matrix;
}

void Layer_initialize_weights(Layer_T layer, float init, float variance)
{
    int n_neurons = Layer_size(layer);
    for (int i = 0; i < n_neurons; i++)
        float2_randomize(layer->weights[i], init, variance);
}

void Layer_set_params(Layer_T layer, param_t params)
{
    assert(params != NULL);
    Layer_initialize_weights(layer, params->w, params->w_var);
    layer->potentiation = params->a_p;
    layer->depression   = params->a_d;
    layer->beta         = params->b;
    layer->threshold    = params->thr;
}

bit2_t Layer_feed(Layer_T layer, bit2_t synapses)
{
    Layer_accumulate(layer, synapses);
    Layer_train(layer);
    return layer->inferences;
}

void Layer_accumulate(Layer_T layer, bit2_t synapses)
{
    /* easy names to access to variables */
    float *current      = layer->currents->data;
    float2_t *weights   = layer->weights;
    bit2_t *syn_pre     = layer->syn_pre;
    float2_t v          = layer->voltages;
    float2_t v_stdp     = layer->voltages_stdp;
    float v_threshold   = layer->threshold;
    bit2_t inf          = layer->inferences;
    bit2_t stdp         = layer->stdp_spikes;
    bit2_t ext_inh      = layer->inter_inhibition;

    int n_neurons = Layer_size(layer);

    /* add incoming synapses to syn_pre, to track which synapses have fired since
    each neurons was last reset  */
    for (int i = 0; i < n_neurons; i++) {
        bit2_or(syn_pre[i], synapses);
    }

    /* calculate input current,
     via matrix multiply [ weights ] x [ synapses] */
    for (int i = 0; i < n_neurons; i++) {
        current[i] = float2_bindot(weights[i], synapses);
    }

    float2_addto(v, layer->currents);
    float2_addto(v_stdp, layer->currents);

    /* find spikes in each accumulators */
    bit2_binset_f2_greater_than(inf, v, v_threshold);
    bit2_binset_f2_greater_than(stdp, v_stdp, v_threshold);

    /* reset inf accumulators that fired */
    float2_inv_binset(v, inf);

    /* reset all stdp accumulators if one has fired */
    float2_zero_if_any(v_stdp, stdp);

    if (ext_inh != NULL) {
        /* update inter layer inhibition matrix */
        /* 1 represents inhibited neuron */
        bit2_or(ext_inh, stdp);

        /* update inter layer inhibition matrix */
        float2_inv_binset(v_stdp, ext_inh);
    }
}

static inline float potentiate(float weight, float potentiation, float beta);
static inline float depress(float weight, float depression);

void Layer_train(Layer_T layer)
{
    /* easy naming and access */
    float2_t *weights = layer->weights;
    bit2_t *syn_pre   = layer->syn_pre;
    bit_t *stdp_arr   = layer->stdp_spikes->data;
    float p = layer->potentiation;
    float d = layer->depression;
    float b = layer->beta;
    int n_neurons = Layer_size(layer);
    int input_size = layer->input_shape.x * layer->input_shape.y;

    /* update weights in layer */
    for (int i = 0; i < n_neurons; i++) {
        /* skip neurons that didn't have stdp spikes */
        if (!stdp_arr[i])
            continue;

        /* input weights and syn_pre array for current neuron */
        bit_t *syn_arr = syn_pre[i]->data;
        float *w       = weights[i]->data;

        for (int j = 0; j < input_size; j++) {
            /* if input neuron fired since last reset of layer neuron */
            if (syn_arr[j])
                w[j] = potentiate(w[j], p, b);
            else
                w[j] = depress(w[j], d);
        }

        /* reset all syn_pre after spike */
        bit2_zero(syn_pre[i]);
    }
}

static inline float potentiate(float weight, float potentiation, float beta)
{
    return weight + potentiation * exp(-beta * weight);
}

static inline float depress(float weight, float depression)
{
    return weight - depression;
}

shape2_t Layer_shape(Layer_T layer)
{
    return &layer->shape;
}

int Layer_size(Layer_T layer)
{
    return layer->shape.x * layer->shape.y;
}

#include <stdlib.h>
#include <string.h>
#include "layer.h"
#include "math.h"
#include "specs.h"
#include "helpful.h"

Layer::Layer(int this_layer)
{
    verify(spec->good(), "config is incomplete");

    /* shorthand variables */
    ConnectedLayerSpec *layer = &(spec->arch.fc_layers[this_layer]);
    int bottom_layer = spec->arch.n_total;
    int top_layer = 0;

    /* set input and output sizes */
    if (this_layer == bottom_layer)
        n_neurons = spec->data.label_channels;
    else
        n_neurons = layer->n_neurons;

    if (this_layer == top_layer)
        n_inputs = spec->data.input_channels;
    else
        n_inputs = layer->n_neurons;

    /* allocate and initialize arrays */
    spikes          = new int[n_neurons];
    times_pre_syn   = new int[n_inputs];
    times_post_syn  = new int[n_neurons];
    voltages        = new float[n_neurons];
    voltages_stdp   = new float[n_neurons];
    weights = new float*[n_neurons];
    for (int j = 0; j < n_neurons; j++)
        weights[j] = new float[n_inputs];

    memset(times_pre_syn,   0, sizeof(int) * n_inputs);
    memset(spikes,          0, sizeof(int) * n_neurons);
    memset(times_post_syn,  0, sizeof(int) * n_neurons);
    memset(voltages,        0, sizeof(float) * n_neurons);
    memset(voltages_stdp,   0, sizeof(float) * n_neurons);

    /* get data from spec */
    v_threshold    = layer->v_threshold;
    stdp_threshold = layer->stdp_threshold;
    potentiation   = spec->learn.potentiation;
    depression     = spec->learn.depression;
    beta           = spec->learn.beta;

    /* initialize weights */
    float init     = layer->weights.initial;
    float variance = layer->weights.variance;

    srand(this_layer);
    for (int j = 0; j < n_neurons; j++) {
        for (int k = 0; k < n_inputs; k++) {
            float v = 2.f * variance * (float)(rand() % 100) / 100.f;
            weights[j][k] = init + (v - variance);
        }
    }

    /* no inhibited neuron */
    winner = -1;
}

Layer::~Layer()
{
    delete [] spikes;
    delete [] times_post_syn;
    delete [] times_pre_syn;
    delete [] voltages;
    delete [] voltages_stdp;

    for (int i = 0; i < n_neurons; i++)
        delete [] weights[i];
    delete [] weights;
}

int *Layer::feed(int *synapses)
{
    reset_inhibition();
    increment_pre_times(synapses);

    /* update voltages */
    for (int i = 0; i < n_neurons; i++) {
        /* dual channel Integrate and Fire neuron */
        float current = dot(weights[i], synapses);

        voltages[i]      = voltages[i] + current;
        voltages_stdp[i] = voltages[i] + current;
    }

    /* spike[i] = 1 iff voltages[i] > v_thresholds[i] */
    set_spikes();
    set_inhibitions();
    if (winner != -1)
        train();

    return spikes;
}

void Layer::reset_inhibition()
{
    winner = -1;
}

float Layer::dot(float *weights, int *synapses)
{
    float dot = 0;

    for (int i = 0; i < n_inputs; i++)
        dot += weights[i] * synapses[i];

    return dot;
}

void Layer::increment_pre_times(int *synapses)
{
    for (int i = 0; i < n_inputs; i++)
        if (synapses[i])
            times_pre_syn[i] = 0;
        else
            times_pre_syn[i]++;
}

void Layer::set_spikes()
{
    for (int i = 0; i < n_neurons; i++)
        if (voltages[i] > v_threshold) {
            voltages[i] = 0;
            spikes[i] = 1;
        } else
            spikes[i] = 0;
}

void Layer::set_inhibitions()
{
    for (int i = 0; i < n_neurons; i++)
        if (voltages_stdp[i] > stdp_threshold)
            winner = i;
        else
            times_post_syn[i]++;

    if (winner == -1) /* no neurons fired */
        return;

    for (int i = 0; i < n_neurons; i++)
        voltages_stdp[i] = 0;
}

void Layer::train()
{
    float *w = weights[winner];

    for (int i = 0; i < n_inputs; i++)
        if (times_pre_syn[i] < times_post_syn[winner])
            w[i] += potentiation * exp(-beta * w[i]);
        else
            w[i] += -depression;

    times_post_syn[winner] = 0;
    return;
}


int Layer::size()
{
    return n_neurons;
}

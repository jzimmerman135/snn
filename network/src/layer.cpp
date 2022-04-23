#include <stdlib.h>
#include <string.h>
#include "layer.h"
#include "math.h"
#include "specs.h"

Layer::Layer(SpecSheet &s, int this_layer)
{
    int bottom_layer = s.n_layers;
    int top_layer = 0;

    if (this_layer == bottom_layer)
        n_neurons = s.n_output_channels;
    else
        n_neurons = s.architecture[this_layer];

    if (this_layer == top_layer)
        n_inputs = s.n_input_channels;
    else
        n_inputs = s.architecture[this_layer - 1];

    spikes          = new int[n_neurons];
    times_pre_syn   = new int[n_inputs];
    times_post_syn  = new int[n_neurons];
    v_thresholds    = new float[n_neurons];
    stdp_thresholds = new float[n_neurons];
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

    size_t fbytes = sizeof(float) * n_neurons;
    memset(v_thresholds,    s.v_thresholds[this_layer], fbytes);
    memset(stdp_thresholds, s.stdp_thresholds[this_layer], fbytes);

    winner = -1;
    potentiation = s.learn_potentiation;
    depression = s.learn_depression;
    beta = s.learn_beta;

    /* initialize weights */
    srand(this_layer);
    float init = s.initial_weights[this_layer];
    float variance = s.initial_weights_variance[this_layer];
    for (int j = 0; j < n_neurons; j++) {
        for (int k = 0; k < n_inputs; k++) {
            float v = 2.f * variance * (float)(rand() % 100) / 100.f;
            weights[j][k] = init + (v - variance);
        }
    }
}

Layer::~Layer()
{
    delete [] spikes;
    delete [] times_post_syn;
    delete [] times_pre_syn;
    delete [] v_thresholds;
    delete [] stdp_thresholds;
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
        if (voltages[i] > v_thresholds[i]) {
            voltages[i] = 0;
            spikes[i] = 1;
        } else {
            spikes[i] = 0;
        }
}

void Layer::set_inhibitions()
{
    for (int i = 0; i < n_neurons; i++)
        if (voltages_stdp[i] > stdp_thresholds[i]) {
            winner = i;
        } else
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

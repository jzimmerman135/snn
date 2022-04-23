#include <stdlib.h>
#include <string.h>
#include "layer.h"
#include "specs.h"

Layer::Layer(SpecSheet &s, int i)
{
    if (i == s.n_layers) /* output layer */
        n_neurons = s.n_output_channels;
    else /* normal hidden layer */
        n_neurons = s.architecture[i];

    if (i == 0) /* input layer */
        n_inputs = s.n_input_channels;
    else /* normal hidden layer */
        n_inputs = s.architecture[i - 1];

    times_pre_syn   = new int[n_inputs];
    spikes          = new int[n_neurons];
    times_post_syn  = new int[n_neurons];
    inhibition      = new int[n_neurons];
    v_thresholds    = new float[n_neurons];
    stdp_thresholds = new float[n_neurons];
    voltages        = new float[n_neurons];
    voltages_stdp   = new float[n_neurons];

    weights = new float*[n_neurons];
    for (int j = 0; j < n_neurons; j++)
        weights[j] = new float[n_inputs];

    initialize(s, i);
}

Layer::~Layer()
{
    delete [] spikes;
    delete [] inhibition;
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
    /* increment times */
    increment_pre_times(synapses);

    /* update voltages */
    for (int i = 0; i < n_neurons; i++) {
        float input_dot = current(weights[i], synapses);

        voltages[i] = voltages[i] + input_dot;
        voltages_stdp[i] = voltages[i] + input_dot;
    }

    set_spikes();
    set_inhibitions();
    train();

    return spikes;
}

int Layer::size()
{
    return n_neurons;
}

void Layer::initialize(SpecSheet &s, int i)
{
    memset(times_pre_syn,   0, sizeof(int) * n_inputs);
    memset(spikes,          0, sizeof(int) * n_neurons);
    memset(times_post_syn,  0, sizeof(int) * n_neurons);
    memset(inhibition,      0, sizeof(int) * n_neurons);
    memset(voltages,        0, sizeof(float) * n_neurons);
    memset(voltages_stdp,   0, sizeof(float) * n_neurons);
    memset(v_thresholds,    s.v_thresholds[i], sizeof(float) * n_neurons);
    memset(stdp_thresholds, s.stdp_thresholds[i], sizeof(float) * n_neurons);

    learn_beta = s.learn_beta;
    learn_alpha = s.learn_alpha;

    float variance = s.initial_weights_variance[i];
    float init = s.initial_weights[i];

    for (int j = 0; j < n_neurons; j++) {
        for (int k = 0; k < n_inputs; k++) {
            float v = 2.f * variance * (float)(rand() % 100) / 100.f;
            weights[j][k] = init + (v - variance);
        }
    }
}

float Layer::current(float *weights, int *synapses)
{
    float dot = 0;

    for (int i = 0; i < n_inputs; i++)
        dot += weights[i] * synapses[i];

    return dot;
}

void Layer::increment_pre_times(int *synapses)
{
    for (int i = 0; i < n_inputs; i++) {
        if (synapses[i]) {
            times_pre_syn[i] = 0;
        } else {
            times_pre_syn[i]++;
        }
    }
}

void Layer::set_spikes()
{
    for (int i = 0; i < n_neurons; i++) {
        if (voltages[i] > v_thresholds[i]) {
            voltages[i] = 0;
            spikes[i] = 1;
        } else {
            spikes[i] = 0;
        }
    }
}

void Layer::set_inhibitions()
{
    for (int i = 0; i < n_neurons; i++) {
        if (voltages_stdp[i] > stdp_thresholds[i]) {
            voltages_stdp[i] = 0;
        }
    }
}

void Layer::train()
{
    int a;
    for (int i = 0; i < n_inputs; i++)
        (void)a;
    return;
}

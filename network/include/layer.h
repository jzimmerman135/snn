#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED

#include "specs.h"

class Layer {
friend class Logger;
public:
    Layer(int i);
    ~Layer();
    int *feed(int *synapses);
    int size();

    int index;

private:
    int n_inputs;
    int n_neurons;

    float **weights;

    int *times_pre_syn;
    int *times_post_syn;
    int *spikes;
    int winner; /* index of non-inhibited neuron */

    float v_threshold;
    float stdp_threshold;
    float *voltages_stdp;
    float *voltages;

    float potentiation;
    float depression;
    float beta;

    void reset_inhibition();

    float dot(float *weights, int *synapses);

    void increment_pre_times(int *synapses);
    void set_spikes();
    void set_inhibitions();
    void train();
};

#endif

#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED

#include "specs.h"

class Layer {
public:
    Layer(SpecSheet &s, int i);
    ~Layer();
    int *feed(int *synapses);
    int size();

private:
    int n_inputs;
    int n_neurons;

    float **weights;

    int *times_pre_syn;
    int *times_post_syn;
    int *spikes;
    int winner; /* index of non-inhibited neuron */

    float *v_thresholds;
    float *stdp_thresholds;
    float *voltages_stdp;
    float *voltages;

    float potentiation;
    float depression;
    float beta;

    void initialize(SpecSheet &spec, int i);
    void reset_inhibition();

    float dot(float *weights, int *synapses);

    void increment_pre_times(int *synapses);
    void set_spikes();
    void set_inhibitions();
    void train();
};

#endif

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
    int *inhibition;
    int *spikes;

    float *v_thresholds;
    float *stdp_thresholds;
    float *voltages_stdp;
    float *voltages;


    float learn_alpha;
    float learn_beta;

    void initialize(SpecSheet &spec, int i);
    float current(float *weights, int *synapses);
    void increment_pre_times(int *synapses);
    void set_spikes();
    void set_inhibitions();
    void train();
};

#endif

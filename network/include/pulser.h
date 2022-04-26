#ifndef PULSE_INCLUDED
#define PULSE_INCLUDED

class Pulser {
public:
    Pulser();
    ~Pulser();

    /* setters */
    void initialize(int n_inputs);
    void set_current(float *inputs);

    /* getters */
    int *spikes();

private:
    int counter;
    int n_inputs;

    float *current; // input data
    int *output; // output spike train
};

#endif

#include <stdlib.h>
#include "matrix.h"
#include "models.h"

#define T Neuron_T

struct T {
    Matrix_T     weights;
    float   voltage_prev;
    float        voltage;
    float      threshold;
    int         n_inputs;
};

T Neuron_new(int n_inputs)
{
    T neuron = malloc(sizeof(struct T));

    neuron->weights = Matrix_new(n_inputs);
    neuron->parent_layer = parent_layer;
    neuron->n_inputs = n_inputs;
}

int Neuron_feed(T neuron, Matrix_T data, int t)
{
    struct T n = *neuron;

    n.voltage = n.voltage_prev + Neuron_current(neuron, data, t);

    spike = n.voltage > n.threshold;
    return spike;
}

static inline void Neuron_current(T neuron, Matrix_T data, int t)
{
    Matrix_T time_vec[neuron->n_inputs] = {t};
    Matrix_T spikes_prev = Matrix_union(data, time_vec);
    Matrix_T input_currents = Matrix_mult(spikes_prev, neuron->weights);
    return Matrix_sum(input_currents);
}

void Neuron_train(T neuron, Matrix_T input, Matrix_T output) {
    (void)neuron;
    (void)input;
    (void)output;
    /* ????? */
    return;
}

void Neuron_free(T *neuron);

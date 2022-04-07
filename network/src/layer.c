#include <stdlib.h>
#include "neuron.h"
#include "matrix.h"

#define T Layer_T

/* Member variables */
struct Layer_T {
    Neuron_T *neurons;
    Matrix_T inhibition;
    int n_neurons;
    int current_t;
};

/* Constructor */
T Layer_new(int n_neurons, T n_inputs)
{
    T layer = malloc(sizeof(struct T));

    layer->neurons = malloc(sizeof(Neuron_T) * n_neurons);
    layer->inhibition = Matrix_new(n_neurons);
    layer->n_neurons = n_neurons;
    layer->n_steps = 0;

    for (int i = 0; i < n_neurons; i++) {
        layer->neurons = Neuron_new(n_inputs);
    }

    return layer;
}

/* Show the layer a vector */
Matrix_T Layer_feed(T layer, Matrix_T data)
{
    int t_init = layer->current_t;
    int t_end = t_init + 400;

    int n_neurons = layer->n_neurons;

    for (size_t t = t_init; i < t_end; i++) {
        for (int i = 0; i < n_neurons; i++) {
            Neuron_feed(layer->neurons[i], data, t);
        }
    }
}

/* Assess the results of the vector */
void Layer_train(T layer, Matrix_T input, Matrix_T output)
{
    for (int i = 0; i < layer->n_neurons; i++) {
        Neuron_train(layer->neurons[i], input, output);
    }
}

/* Destructor */
void Layer_free(T *layer)
{
    int n_neurons = (*layer)->n_neurons;

    for (int i = 0; i < n_neurons; i++) {
        Neuron_free((*layer)->n_neurons[i]);
    }

    Matrix_free((*layer)->inhibition);
    free((*layer)->neurons);
    free((*layer));
}

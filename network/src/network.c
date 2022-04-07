#include <stdlib.h>
#include "layer.h"
#include "matrix.h"

#define T Network_T

struct T {
    Layer_T *layers;
    int n_layers;
    int  n_steps;
};

T Network_new(int n_layers, int *architecture)
{
    T network = malloc(sizeof(struct T));

    network->layers = malloc(sizeof(Layer_T) * n_layers);
    network->n_layers = n_layers;
    network->n_steps = 0;

    for (int i = 0; i < n_layers; i++) {
        network->layers[i] = Layer_new(architecture[i]);
    }

    return network;
}

Matrix_T Network_feed(T network, Matrix_T data)
{
    Matrix_T input = Input_prep(data);

    int n_layers = network->n_layers;

    for (int i = 0; i < n_layers; i++) {
        Matrix_T result = Layer_feed(network->layers[i], input);
        Layer_train(network->layers[i], input, result);
        input = result;
    }

    network->n_steps++;

    return result;
}

void Network_free(T *network)
{
    int n_layers = (*network)->n_layers;

    for (int i = 0; i < n_layers; i++) {
        Layer_free((*network)->layers[i]);
    }

    free((*network)->layers);
    free(*network);
}

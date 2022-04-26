#include <iostream>
#include "pulser.h"

Pulser::Pulser()
{
    counter = 0;
    n_inputs = 0;

    current = nullptr;
    output = nullptr;
}

Pulser::~Pulser()
{
    delete [] current;
    delete [] output;
}

void Pulser::initialize(int n)
{
    n_inputs = n;
    current = new float[n_inputs];
    output = new int[n_inputs];

    for (int i = 0; i < n_inputs; i++) {
        current[i] = 0;
        output[i] = 0;
    }
}

void Pulser::set_current(float *inputs)
{
    for (int i = 0; i < n_inputs; i++)
        current[i] = inputs[i];
}

int *Pulser::spikes()
{
    counter++;
    return output;
}

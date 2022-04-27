#include <iostream>
#include "pulser.h"
#include "specs.h"

Pulser::Pulser()
{
    n_inputs = spec->data.input_channels;
    current = new float[n_inputs];
    output = new int[n_inputs];

    for (int i = 0; i < n_inputs; i++) {
        current[i] = 0;
        output[i] = 0;
    }
}

Pulser::~Pulser()
{
    delete [] current;
    delete [] output;
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

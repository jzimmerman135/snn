#include <iostream>
#include "pulser.h"
#include "specs.h"

using namespace std;

Pulser::Pulser()
{
    n_inputs = spec->data.input_channels;
    current = new float[n_inputs];
    output = new int[n_inputs];
    voltages = new float[n_inputs];
    deltas = new float[n_inputs];

    tau = 1.5;

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

void Pulser::set_tau(float t)
{
    tau = t;
}

int *Pulser::spikes()
{
    for (int i = 0; i < n_inputs; i++) {
        deltas[i] = -voltages[i] * (1 - voltages[i]) / tau + current[i];
        voltages[i] = voltages[i] + deltas[i];
    }

    for (int i = 0; i < n_inputs; i++) {
        if (voltages[i] > 1) {
            voltages[i] = 0;
            output[i] = 1;
        }
        else
            output[i] = 0;
    }

    return output;
}

int Pulser::size()
{
    return n_inputs;
}

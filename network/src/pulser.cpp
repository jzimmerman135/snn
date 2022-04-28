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

int *Pulser::spikes()
{
    // cout << "CURRENT: ";
    // for (int i = 0; i < n_inputs; i++)
    //     cout << current[i] << ",";
    // cout << endl;
    //
    // cout << "VOLTAGES: ";
    // for (int i = 0; i < n_inputs; i++)
    //     cout << voltages[i] << ",";
    // cout << endl;
    //
    // cout << "DELTAS: ";
    // for (int i = 0; i < n_inputs; i++)
    //     cout << deltas[i] << ",";
    // cout << endl;

    for (int i = 0; i < n_inputs; i++) {
        deltas[i] = -voltages[i] * (1 - voltages[i])/tau + current[i];
        voltages[i] = voltages[i] + deltas[i];
    }

    // cout << deltas[2] << endl;

    for (int i = 0; i < n_inputs; i++) {
        if (voltages[i] > 1) {
            voltages[i] = 0;
            output[i] = 1;
        }
        else {
            output[i] = 0;
        }
    }

    return output;
}

#include <iostream>
#include <fstream>
#include "logger.h"

using namespace std;

Logger::Logger()
{
    save_requested = spec->recording.save;
}

Logger::~Logger()
{
    for (int i = 0; i < count; i++) {
        delete [] Wj[i];
    }
}

bool Logger::save()
{
    return save_requested;
}

void Logger::write()
{
    if (!save_requested)
        return;

    cout << "writing data to " << spec->recording.filename << "\n";
    return;
}

void Logger::log(Layer layer, int time, int input_idx)
{
    count++;

    int n_neurons = layer.size();
    for (int i = 0; i < n_neurons; i++) {
        t.push_back(time);

        j.push_back(i+1);
        l.push_back(layer.index);

        input.push_back(input_idx);
        spike.push_back(layer.spikes[i]);

        V.push_back(layer.voltages[i]);
        Vstdp.push_back(layer.voltages_stdp[i]);

        float *weights_vec = new float[layer.n_inputs];
        for (int k = 0; k < layer.n_inputs; k++) {
            weights_vec[k] = layer.weights[i][k];
        }
        Wj.push_back(weights_vec);

        nprev.push_back(layer.n_inputs);
        Linh.push_back(layer.winner);
    }

    return;
}

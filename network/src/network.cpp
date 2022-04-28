#include "network.h"
#include "specs.h"
#include "helpful.h"
#include "reader.h"

Network::Network()
{
    train_data.read_input_data(spec->data.train_filename);
    test_data.read_input_data(spec->data.test_filename);
    verify(spec->data.input_channels && spec->data.label_channels,
            "0 input channels or 0 label channels");

    n_output_channels = spec->data.label_channels;
    output = new int[n_output_channels];
    classification = new int[n_output_channels];


    return;
}

Network::~Network()
{
    delete [] output;
    delete [] classification;
    return;
}

void Network::train()
{
    train_score = run(train_data);
    return;
}

void Network::test()
{
    test_score = run(test_data);
    return;
}


float Network::run(Reader &dataset)
{
    int c_thru_data = spec->cycles.through_data;
    int c_per_input = spec->cycles.per_input;
    int n_inputs = dataset.n_elem();
    int *spike_train;
    float score = 0;

    for (int i = 0; i < c_thru_data; i++) {
        for (int j = 0; j < n_inputs; j++) {

            encoder.set_current(dataset.input(j));

            for (int k = 0; k < c_per_input; k++) {

                spike_train = encoder.spikes();
                output = feed(spike_train);
                classification = classify(output);

            }

            score += evaluate(classification, dataset.label(j));
        }
    }

    return score;
}

int *Network::feed(int *spike_train)
{
    for (int i = 0; i < n_output_channels; i++)
        output[i] = spike_train[i];

    return output;
}

int *Network::classify(int *output_spikes)
{
    for (int i = 0; i < n_output_channels; i++)
        classification[i] += output_spikes[i];

    return classification;
}

float Network::evaluate(int *classification, float *labels)
{
    (void)labels, (void)classification;
    return 1.f;
}

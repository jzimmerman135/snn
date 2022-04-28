#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "specs.h"
#include "pulser.h"
#include "reader.h"
#include "logger.h"

class Network {
public:
    Network();
    ~Network();
    void train();
    void test();
private:
    float run(Reader &dataset);

    int *feed(int *input_spikes);
    int *classify(int *output_spikes);
    float evaluate(int *classification, float *labels);

    Reader train_data;
    Reader test_data;
    Logger record;
    Pulser encoder;

    int n_output_channels;

    int *output;
    int *classification;

    float train_score;
    float test_score;
};

#endif

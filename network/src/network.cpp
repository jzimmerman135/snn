#include "network.h"
#include "specs.h"

Network::Network(SpecSheet &specs)
{
    train_data.read_input_data(specs.train_data_filename);
    test_data.read_input_data(specs.test_data_filename);
    encoder.initialize(specs.n_input_channels);
    return;
}

Network::~Network()
{
    return;
}

void Network::train()
{
    return;
}

void Network::test()
{
    return;
}

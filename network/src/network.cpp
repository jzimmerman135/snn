#include "network.h"
#include "specs.h"

Network::Network()
{
    train_data.read_input_data(spec->data.train_filename);
    test_data.read_input_data(spec->data.test_filename);
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

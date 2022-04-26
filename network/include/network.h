#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "specs.h"
#include "pulser.h"
#include "reader.h"

class Network {
public:
    Network(SpecSheet &specs);
    ~Network();
    void train();
    void test();
private:
    Reader train_data;
    Reader test_data;
    Pulser encoder;
};

#endif

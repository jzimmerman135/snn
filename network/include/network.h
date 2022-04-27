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
    Reader train_data;
    Reader test_data;
    Logger record;
    Pulser encoder;
};

#endif

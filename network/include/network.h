#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "specs.h"
#include "pulse.h"
#include "reader.h"

class Network {
public:
    Network(SpecSheet &specs);
    ~Network();
    void train();
    void test();
private:
    Reader inputs;
    Pulse  pulser;
};

#endif

#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "matrix.h"
#include "reader.h"

typedef struct Network_T *Network_T;

typedef struct Arch_T {
    int n_cv;
    int n_fc;
    int z;
} *Arch_T;

extern Network_T Network_new(Arch_T arch, shape2_t input, shape2_t label);
extern void Network_free(Network_T *net);
extern bit2_t Network_feed(Network_T net, bit2_t spikes);

#endif

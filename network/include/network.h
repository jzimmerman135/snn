#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "matrix.h"
#include "reader.h"

typedef struct Network_T *Network_T;

extern Network_T Network_new(shape2_t input, shape2_t label);
extern void Network_free(Network_T *net);
extern void Network_add_layer(Network_T net, shape2_t shape);
extern void Network_add_filter(Network_T net, shape2_t shape, int n_filters);
extern int Network_feed(Network_T net, float2_t input, float2_t label);

#endif

#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED

#include "matrix.h"
#include "reader.h"
#include "layer.h"
#include "filter.h"
#include "logger.h"

typedef struct Network_T *Network_T;

extern Network_T Network_new(shape2_t input, shape2_t label);
extern void Network_free(Network_T *net);
extern void Network_add_layer(Network_T net, shape2_t shape, param_t params);
extern void Network_add_filter(Network_T net, shape2_t shape, int n_filters,
                               param_t params);
extern int Network_feed(Network_T net, float2_t input, float2_t label,
                        Log_T log);
extern Layer_T Network_layer_at(Network_T net, int i);
extern Filter_T Network_filter_at(Network_T net, int i);

/*
private void propagate_spikes(Network_T net);         // just for clarity
*/

#endif

#ifndef FILTER_INCLUDED
#define FILTER_INCLUDED

#include "layer.h"
#include "matrix.h"

typedef struct Filter_T *Filter_T;
struct Filter_T {
    struct shape2_t f_shape; /* shape of each feature map */
    struct shape2_t output_shape; /* overall shape */

    int n_filters;

    Layer_T *layers;
    bit2_t inter_inhibition;

    bit2_t spikes;
};

extern Filter_T Filter_new(shape2_t filter_shape, shape2_t input_shape,
                           int n_filters);

extern void Filter_free(Filter_T *filter);
extern void Filter_set_params(Filter_T filter, param_t params);
extern bit2_t Filter_feed(Filter_T filter, bit2_t synapse);
extern shape2_t Filter_shape(Filter_T filter);

#endif

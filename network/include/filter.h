#ifndef FILTER_INCLUDED
#define FILTER_INCLUDED

#include "layer.h"
#include "matrix.h"

typedef struct Filter_T *Filter_T;

extern Filter_T Filter_new(shape2_t filter_shape, shape2_t input_shape,
                           int n_filters);

extern void Filter_free(Filter_T *filter);

extern bit2_t Filter_feed(Filter_T filter, bit2_t synapse);
extern shape2_t Filter_shape(Filter_T filter);

#endif

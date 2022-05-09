#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED

#include <stdlib.h>
#include "matrix.h"

/* use to define a 2 dimensional layer's shape */
typedef struct shape2_t *shape2_t;
struct shape2_t {
    int x;
    int y;
};

/* parameters to initialize a layer */
typedef struct param_t *param_t;
struct param_t {
    float w;
    float w_var;
    float a_p; /* alpha potentiation */
    float a_d; /* alpha depression */
    float b;   /* beta learn rate */
    float thr; /* membrane threshold */
};

typedef struct Layer_T *Layer_T;
struct Layer_T {
    struct shape2_t shape;
    struct shape2_t input_shape;

    /* n_neurons == shape.x * shape.y */

    float2_t *weights; /* n_neurons x [input shape] */
    bit2_t   *syn_pre; /* n_neurons x [input shape] */

    float2_t currents;      /* [shape] */
    float2_t voltages;      /* [shape] */
    float2_t voltages_stdp; /* [shape] */

    bit2_t inferences;  /* [shape] */
    bit2_t stdp_spikes; /* [shape] */

    bit2_t inter_inhibition; /* [shape], defined externally */

    float threshold;
    float potentiation;
    float depression;
    float beta;
};

/* use to create and destroy a hidden layer of shape, given its input shape */
extern Layer_T Layer_new(shape2_t shape, shape2_t input_shape);
extern void Layer_free(Layer_T *layer);

/* use to link a layer to an external inhibition matrix,
   to build inter layer inhibition */
extern void Layer_connect_inhibition(Layer_T layer, bit2_t inh_matrix);

/* feed a layer a matrix of synapses */
extern bit2_t Layer_feed(Layer_T layer, bit2_t synapses);

extern void Layer_set_params(Layer_T layer, param_t params);

/* get layer info */
extern shape2_t Layer_shape(Layer_T layer);
extern int Layer_size(Layer_T layer);


#endif

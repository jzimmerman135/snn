#ifndef ENCODER_INCLUDED
#define ENCODER_INCLUDED

#include <stdlib.h>
#include "layer.h"
#include "matrix.h"

typedef struct Encoder_T *Encoder_T;
extern Encoder_T Encoder_new(shape2_t shape);
extern void Encoder_free(Encoder_T *e);
extern void Encoder_set_current(Encoder_T e, float *currents);
extern bit2_t Encoder_spikes(Encoder_T e);
extern shape2_t Encoder_shape(Encoder_T e);
#endif

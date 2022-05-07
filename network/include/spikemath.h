#ifndef SPIKEMATH_INCLUDED
#define SPIKEMATH_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

extern void float2_addto(float2_t f2_dest, float2_t f2_src);
extern float float2_bindot(float2_t f2, bit2_t b2);
extern void float2_binset(float2_t f2, bit2_t b2);
extern void float2_inv_binset(float2_t f2, bit2_t b2);
extern void float2_binsubtract(float2_t f2, bit2_t b2); /* spike encoder */
extern void float2_zero_if_any(float2_t f2, bit2_t b2);

extern void bit2_binset_f2_greater_than(bit2_t b2, float2_t f2, float cmp);
extern void bit2_or(bit2_t b2_dest, bit2_t b2_src);
extern void bit2_zero(bit2_t b2);

#endif

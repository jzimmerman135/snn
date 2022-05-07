#ifndef SPIKEMATH_INCLUDED
#define SPIKEMATH_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/* add src to dest */
extern void float2_addto(float2_t f2_dest, float2_t f2_src);

/* return sum of f2 where b2 is true */
extern float float2_bindot(float2_t f2, bit2_t b2);

/* f2 = 0 if b2 is false */
extern void float2_binset(float2_t f2, bit2_t b2);

/* f2 = 0 if b2 is true */
extern void float2_inv_binset(float2_t f2, bit2_t b2);

/* f2 - 1 if b2 is true */
extern void float2_binsubtract(float2_t f2, bit2_t b2); /* spike encoder */

/* ALL f2 = 0 if ANY b2 is true */
extern void float2_zero_if_any(float2_t f2, bit2_t b2);

/* b2 = 1 if f2 > target */
extern void bit2_binset_f2_greater_than(bit2_t b2, float2_t f2, float target);

/* dest = (src || dest) */
extern void bit2_or(bit2_t b2_dest, bit2_t b2_src);

/* all b2 = 0 */
extern void bit2_zero(bit2_t b2);

/* append src to dest at index i */
/* must have same y value and dest x value must be multiple of y */
extern void bit2_append(bit2_t b2_dest, bit2_t b2_src, int i);


#endif

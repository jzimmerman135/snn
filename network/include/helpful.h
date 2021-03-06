#ifndef HELPFUL_INCLUDED
#define HELPFUL_INCLUDED

#include "matrix.h"
#include "stdio.h"
#include "assert.h"

/* debug print */
extern void fprintarrf(float *arr, int n_elem, FILE *fp);
extern void fprintarrb(bit_t *arr, int n_elem, FILE *fp);
extern void fprintshp(char *msg, void *shp, FILE *fp);

/* random float [0, 1] */
extern float random_zero_one();


#endif

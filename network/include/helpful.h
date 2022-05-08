#ifndef HELPFUL_INCLUDED
#define HELPFUL_INCLUDED

#include "matrix.h"
#include "stdio.h"
#include "assert.h"

extern void fprintarrf(float *arr, int n_elem, FILE *fp);
extern void fprintarrb(bit_t *arr, int n_elem, FILE *fp);
extern void fprintshp(char *msg, void *shp, FILE *fp);

#endif

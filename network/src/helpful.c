#include "helpful.h"
#include <stdio.h>
#include <stdlib.h>
#include "layer.h"

void fprintarrf(float *arr, int n_elem, FILE *fp)
{
    fprintf(fp, "[ ");
    for (int i = 0; i < n_elem; i++)
        fprintf(fp, "%.3f,", arr[i]);
    fprintf(fp, "\b ]\n");
}


void fprintarrb(bit_t *arr, int n_elem, FILE *fp)
{
    fprintf(fp, "[ ");
    for (int i = 0; i < n_elem; i++)
        fprintf(fp, "%i, ", arr[i]);
    fprintf(fp, "\b\b ]\n");
}

void fprintshp(char *msg, void *shp, FILE *fp)
{
    shape2_t shape = (shape2_t)shp;
    fprintf(fp, "%s[%i x %i]\n", msg, shape->x, shape->y);
}

float random_zero_one()
{
    return (float)rand()/(float)(RAND_MAX);
}

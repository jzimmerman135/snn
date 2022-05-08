#include "helpful.h"
#include <stdio.h>

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

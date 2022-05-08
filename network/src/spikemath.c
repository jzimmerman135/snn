#include "spikemath.h"
#include <string.h>

void float2_addto(float2_t f2_dest, float2_t f2_src)
{
    int size = f2_dest->x * f2_dest->y;
    float *dest_data = f2_dest->data;
    float *src_data = f2_src->data;

    for (int i = 0; i < size; i++) {
        dest_data[i] += src_data[i];
    }
}

float float2_bindot(float2_t f2, bit2_t b2)
{
    int size = f2->x * f2->y;
    float *fdata = f2->data;
    bit_t *bdata = b2->data;

    float sum = 0;
    for (int i = 0; i < size; i++) {
        if (bdata[i])
            sum += fdata[i];
    }

    return sum;
}

void float2_binset(float2_t f2, bit2_t b2)
{
    int size = f2->x * f2->y;
    float *fdata = f2->data;
    bit_t *bdata = b2->data;

    for (int i = 0; i < size; i++) {
        fdata[i] *= 1 && bdata[i];
    }
}

void float2_inv_binset(float2_t f2, bit2_t b2)
{
    int size = f2->x * f2->y;
    float *fdata = f2->data;
    bit_t *bdata = b2->data;

    for (int i = 0; i < size; i++) {
        fdata[i] *= !bdata[i];
    }
}

void float2_binsubtract(float2_t f2, bit2_t b2)
{
    int size = f2->x * f2->y;
    float *fdata = f2->data;
    bit_t *bdata = b2->data;

    for (int i = 0; i < size; i++) {
        fdata[i] -= 1 && bdata[i];
    }
}

void float2_zero_if_any(float2_t f2, bit2_t b2)
{
    int size = f2->x * f2->y;
    float *fdata = f2->data;
    bit_t *bdata = b2->data;

    for (int i = 0; i < size; i++) {
        if (bdata[i]) {
            memset(fdata, 0, sizeof(float) * size);
            break;
        }
    }
}

void bit2_binset_f2_greater_than(bit2_t b2, float2_t f2, float target)
{
    int size = f2->x * f2->y;
    bit_t *bdata = b2->data;
    float *fdata = f2->data;

    for (int i = 0; i < size; i++) {
        bdata[i] = fdata[i] > target;
    }
}

void bit2_or(bit2_t b2_dest, bit2_t b2_src)
{
    int size = b2_dest->x * b2_src->y;
    bit_t *dest_data = b2_dest->data;
    bit_t *src_data = b2_src->data;

    for (int i = 0; i < size; i++) {
        dest_data[i] = dest_data[i] || src_data[i];
    }
}

void bit2_zero(bit2_t b2)
{
    int size = b2->x * b2->y;
    bit_t *bdata = b2->data;

    memset(bdata, 0, sizeof(bit_t) * size);
}

extern void bit2_append(bit2_t b2_dest, bit2_t b2_src, int i)
{
    int size = b2_dest->x * b2_src->y;
    bit_t *dest_data = b2_dest->data;
    bit_t *src_data = b2_src->data;

    memcpy(dest_data + size * i, src_data, size);
}

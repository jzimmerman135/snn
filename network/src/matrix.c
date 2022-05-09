#include <stdlib.h>
#include "matrix.h"
#include <string.h>
#include <stdio.h>
#include "assert.h"

/*
static inline int idx2(int x, int y, int x_max)
{
    return x + x_max * y;
}

static inline int idx3(int x, int y, int z, int x_max, int y_max)
{
    return x + x_max * y + x_max * y_max * z;
}
*/

/******************************************************************************
                                float2_t
******************************************************************************/

float2_t float2_new(int x, int y)
{
    float2_t f2 = malloc(sizeof(struct float2_t));
    f2->data = malloc(sizeof(float) * x * y);
    f2->x = x;
    f2->y = y;
    memset(f2->data, 0, sizeof(float) * x * y);
    return f2;
}

void float2_free(float2_t *f2)
{
    free((*f2)->data);
    free(*f2);
    *f2 = NULL;
}

/******************************************************************************
                                float3_t
******************************************************************************/

float3_t float3_new(int x, int y, int z)
{
    float3_t f3 = malloc(sizeof(struct float3_t));
    f3->data = malloc(sizeof(float) * x * y * z);
    f3->x = x;
    f3->y = y;
    f3->z = z;
    memset(f3->data, 0, sizeof(float) * x * y * z);
    return f3;
}

void float3_free(float3_t *f3)
{
    free((*f3)->data);
    free(*f3);
    *f3 = NULL;
}

/******************************************************************************
                                bit2_t
******************************************************************************/

bit2_t bit2_new(int x, int y)
{
    bit2_t b2 = malloc(sizeof(struct bit2_t));
    b2->data = malloc(sizeof(bit_t) * x * y);
    b2->x = x;
    b2->y = y;
    memset(b2->data, 0, sizeof(bit_t) * x * y);

    return b2;
}

void bit2_free(bit2_t *b2)
{
    free((*b2)->data);
    free(*b2);
    *b2 = NULL;
}

/******************************************************************************
                                bit3_t
******************************************************************************/

bit3_t bit3_new(int x, int y, int z)
{
    bit3_t b3 = malloc(sizeof(struct bit3_t));
    b3->data = malloc(sizeof(int) * x * y * z);
    b3->x = x;
    b3->y = y;
    b3->z = z;
    memset(b3->data, 0, sizeof(int) * x * y * z);
    return b3;
}

void bit3_free(bit3_t *b3)
{
    free((*b3)->data);
    free(*b3);
    *b3 = NULL;
}

/******************************************************************************
                                int2_t
******************************************************************************/

int2_t int2_new(int x, int y)
{
    int2_t i2 = malloc(sizeof(struct int2_t));
    i2->data = malloc(sizeof(int) * x * y);
    i2->x = x;
    i2->y = y;
    memset(i2->data, 0, sizeof(int) * x * y);
    return i2;
}

void int2_free(int2_t *i2)
{
    free((*i2)->data);
    free(*i2);
    *i2 = NULL;
}

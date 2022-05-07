#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

typedef struct float2_t *float2_t;
struct float2_t {
    int x;
    int y;
    float *data;
};
extern float2_t float2_new(int x, int y);
extern void float2_free(float2_t *f2);


typedef struct float3_t *float3_t;
struct float3_t {
    int x;
    int y;
    int z;
    float *data;
};
extern float3_t float3_new(int x, int y, int z);
extern void float3_free(float3_t *f3);


typedef int bit_t;

typedef struct bit2_t *bit2_t;
struct bit2_t {
    int x;
    int y;
    bit_t *data;
};
extern bit2_t bit2_new(int x, int y);
extern void bit2_free(bit2_t *b2);


typedef struct bit3_t *bit3_t;
struct bit3_t {
    int x;
    int y;
    int z;
    bit_t *data;
};
extern bit3_t bit3_new(int x, int y, int z);
extern void bit3_free(bit3_t *b3);

typedef struct int2_t *int2_t;
struct int2_t {
    int x;
    int y;
    int *data;
};
extern int2_t int2_new(int x, int y);
extern void int2_free(int2_t *i2);

#endif

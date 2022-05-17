#include <stdio.h>
#include "classifier.h"
#include "helpful.h"

struct Classifier_T {
    struct shape2_t shape;
    float accuracy;
    int2_t accumulators;
};

Classifier_T Classifier_new(shape2_t shape)
{
    Classifier_T c = malloc(sizeof(struct Classifier_T));

    c->shape = *shape;
    c->accumulators = int2_new(shape->x, shape->y);
    return c;
}

void Classifier_free(Classifier_T *c)
{
    int2_free(&(*c)->accumulators);
    free(*c);
}

void Classifier_feed(Classifier_T c, bit2_t spikes)
{
    int size = c->shape.x * c->shape.y;
    int *acc_arr = c->accumulators->data;
    bit_t *spike_arr = spikes->data;

    for (int i = 0; i < size; i++)
        acc_arr[i] += (1 && spike_arr[i]);
}

int Classifier_decision(Classifier_T c)
{
    int max_index = 0;
    int max_val = 0;

    int size = c->shape.x * c->shape.y;
    int *acc_arr = c->accumulators->data;

    for (int i = 0; i < size; i++)
        if (acc_arr[i] > max_val)
            max_index = i;

    return max_index;
}

float Classifier_MSE(Classifier_T c, float2_t label)
{
    int size = c->shape.x * c->shape.y;
    int   *acc_arr = c->accumulators->data;
    float *lab_arr = label->data;

    int   acc_sum = 0;
    float lab_sum = 0;
    for (int i = 0; i < size; i++) {
        acc_sum += acc_arr[i];
        lab_sum += lab_arr[i];
    }

    float mse = 0;

    for (int i = 0; i < size; i++) {
        float acc_norm = (float) acc_arr[i] / (float) acc_sum;
        float lab_norm = lab_arr[i] / lab_sum;
        float diff = acc_norm - lab_norm;
        mse += diff * diff;
    }

    return mse / (float) size;
}

int Classifier_total_spikes(Classifier_T c)
{
    int total = 0;
    int size = c->shape.x * c->shape.y;
    int *acc_arr = c->accumulators->data;

    for (int i = 0; i < size; i++)
        total += acc_arr[i];

    return total;
}

void Classifier_reset(Classifier_T c)
{
    int size = c->shape.x * c->shape.y;
    int *acc_arr = c->accumulators->data;

    for (int i = 0; i < size; i++)
        acc_arr[i] = 0;
}

void Classifier_print_summary(Classifier_T c)
{
    printf("CLASSIFIER ACCUMULATOR RESULTS:\n");

    int size = c->shape.x * c->shape.y;
    int *acc_arr = c->accumulators->data;

    printf("[ ");
    for (int i = 0; i < size; i++)
        printf("%i, ", acc_arr[i]);
    printf("\b\b ]\n");
}

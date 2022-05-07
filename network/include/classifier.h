#ifndef CLASSIFIER_INCLUDED
#define CLASSIFIER_INCLUDED

#include "matrix.h"
#include "layer.h"

typedef struct Classifier_T *Classifier_T;
extern Classifier_T Classifier_new(shape2_t shape);
extern void Classifier_free(Classifier_T *c);
extern void Classifier_feed(Classifier_T c, bit2_t spikes);

extern int Classfier_decision(Classifier_T c);
extern float Classifier_MSE(Classifier_T c, float2_t label);
extern int Classifier_total_spikes(Classifier_T c);
extern void Classifier_reset(Classifier_T c);

extern void Classifier_print_summary(Classifier_T c);

#endif

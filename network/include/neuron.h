#ifndef NEURON_INCLUDED
#define NEURON_INCLUDED
#define T Neuron_T
typedef struct T *T;
extern T Neuron_new(int n_inputs);
extern int Neuron_feed(T neuron, Matrix_T data);
extern void Neuron_train(T neuron, Matrix_T input, Matrix_T output);
extern void Neuron_free(T *neuron);
#endif

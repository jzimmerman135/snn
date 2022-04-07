#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED
#define T Layer_T
typedef struct T *T;
extern T Layer_new(int n_neurons, int n_inputs);
extern Matrix_T Layer_feed(T layer, Matrix_T data);
extern void Layer_train(T layer, Matrix_T input, Matrix_T output);
extern void Layer_free(T *layer);
#endif

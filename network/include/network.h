#ifndef NETWORK_INCLUDED
#define NETWORK_INCLUDED
#define T Network_T
typedef struct T *T;
extern T Network_new(int n_layers, int *architecture);
extern Matrix_T Network_feed(T network, Matrix_T data);
extern void Network_free(T *network);
#endif

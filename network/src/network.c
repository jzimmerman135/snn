#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "layer.h"

struct Network_T {
    shape2_t input_shape;
    shape2_t label_shape;
    int n_cv;
    int n_fc;
    Layer_T *fc_layers;
};

Network_T Network_new(Arch_T arch, shape2_t input, shape2_t label)
{
    Network_T net = malloc(sizeof(Network_T));

    net->input_shape = input;
    net->label_shape = label;
    net->n_cv = arch->n_cv;
    net->n_fc = arch->n_fc;

    net->fc_layers = malloc(sizeof(Layer_T) * net->n_fc);
    for (int i = 0; i < net->n_fc; i++)
        net->fc_layers[i] = NULL;

    shape2_t shp = malloc(sizeof(struct shape2_t));
    shp->x = 6;
    shp->y = 1;

    net->fc_layers[0] = Layer_new(shp, input);
    net->fc_layers[1] = Layer_new(label, shp);

    free(shp);

    return net;
}

void Network_free(Network_T  *net)
{
    Layer_free(&(*net)->fc_layers[0]);
    Layer_free(&(*net)->fc_layers[1]);

    free((*net)->fc_layers);
    free(*net);
}


bit2_t Network_feed(Network_T net, bit2_t spikes)
{
    (void)net, (void)spikes;
    return NULL;
}

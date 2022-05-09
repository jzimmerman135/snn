#include "filter.h"
#include "spikemath.h"
#include "assert.h"

Filter_T Filter_new(shape2_t filter_shape, shape2_t input_shape, int n_filters)
{
    Filter_T filter = malloc(sizeof(struct Filter_T));

    filter->f_shape = *filter_shape;
    filter->output_shape.x = filter_shape->x * n_filters;
    filter->output_shape.y = filter_shape->y;

    filter->n_filters = n_filters;

    filter->inter_inhibition = bit2_new(filter->f_shape.x, filter->f_shape.y);
    filter->spikes = bit2_new(filter->output_shape.x, filter->output_shape.y);
    filter->layers = malloc(sizeof(Layer_T) * n_filters);

    for (int i = 0; i < n_filters; i++) {
        filter->layers[i] = Layer_new(filter_shape, input_shape);
        Layer_connect_inhibition(filter->layers[i], filter->inter_inhibition);
    }

    return filter;
}

void Filter_free(Filter_T *filter)
{
    for (int i = 0; i < (*filter)->n_filters; i++)
        Layer_free(&(*filter)->layers[i]);

    bit2_free(&(*filter)->inter_inhibition);
    free(*filter);
}

bit2_t Filter_feed(Filter_T filter, bit2_t synapses)
{
    int n_filters = filter->n_filters;

    bit2_t output = NULL;
    for (int i = 0; i < n_filters; i++) {
         output = Layer_feed(filter->layers[i], synapses);
         bit2_append(filter->spikes, output, i);
    }

    return filter->spikes;
}

shape2_t Filter_shape(Filter_T filter)
{
    return &filter->output_shape;
}

void Filter_set_params(Filter_T filter, param_t params)
{
    assert(params != NULL);
    for (int i = 0; i < filter->n_filters; i++) {
        Layer_set_params(filter->layers[i], params);
    }
}

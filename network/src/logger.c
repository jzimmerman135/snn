#include "logger.h"
#include "string.h"

#define MAX_LINES 100000

static void Log_print_head(Log_T log);

Log_T Log_open(char *filename)
{
    /* add path to filename */
    Log_T log = malloc(sizeof(struct Log_T));

    log->fp = fopen(filename,"w");
    if (log->fp == NULL) {
        fprintf(stderr, "Error: failed to open log file %s\n", filename);
        exit(1);
    }

    log->line_count = 0;
    log->time = 0;
    log->input_index = 0;

    Log_print_head(log);

    return log;
}

void Log_close(Log_T *log)
{
    if (*log == NULL)
        return;

    fclose((*log)->fp);
    free(*log);
    *log = NULL;
}


/*
 *  log->time stores a continuous counter
 *  to get number of neurons in a layer use Layer_size(layer)
 *  to get number of other info use weights layer->voltages->data[i]
 *  to get weights use layer->weights[i]->data[j] for the jth input neuron weight
 *
 *  example id: 401 means filter 3 layer 1
 *       or id: 2 means layer 2 outside of a filter
 *          id: a0b means filter a - 1, layer b
 *
 */
void Log_layer(Log_T log, Layer_T layer, int id)
{
    if (++log->line_count > MAX_LINES) {
        if (log->line_count == MAX_LINES)
            fprintf(stderr, "Error: Max log lines exceeded, logging ended\n");
        else
            return;
    }

    int n_neurons = Layer_size(layer);
    int n_input_neurons = layer->input_shape.x * layer->input_shape.y;
    for (int i = 0; i < n_neurons; i++) {
        int t           = log->time;
        int input_idx   = log->input_index;
        int idx         = i;
        float v         = layer->voltages->data[i];
        float stdp      = layer->voltages_stdp->data[i];
        float *w        = layer->weights[i]->data;

        fprintf(log->fp, "%i,%i,%i,%i,%.3f,%.3f,",
                t, input_idx, idx, id, v, stdp);

        for (int j = 0; j < n_input_neurons; j++) {
            fprintf(log->fp, "%.3f,", w[j]);
        }

        fprintf(log->fp,"\b\n");
    }
}

void Log_filter(Log_T log, Filter_T filter, int id)
{
    int size = filter->n_filters;
    for (int i = 0; i < size; i++)
        Log_layer(log, filter->layers[i], id + ((i + 1) * 100));
}

static void Log_print_head(Log_T log)
{
    fprintf(log->fp, "t,input_idx,idx,id,v,stdp,[w]\n");
}

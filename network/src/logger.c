#include "logger.h"

#include "string.h"

Log_T Log_open(char *filename)
{
    /* add path to filename */
    char path[50] = "../analysis/output/";
    strcat(path, filename);
    filename = path;

    /* add modifiers before creating file */
    strcat(filename, ".out");

    return fopen(filename,"w");
}

void Log_close(Log_T *log)
{
    if (*log == NULL)
        return;

    fclose((*log));
    *log = NULL;
}

/* example id: 401 means filter 3 layer 1
    or     id: 2 means layer 2 outside of a filter
           id: a0b means filter a - 1, layer b
*/

void Log_layer(Log_T log, Layer_T layer, int time, int id)
{
    fprintf(log, "%i, %i, %i\n",
            Layer_size(layer), time, id);
}

void Log_filter(Log_T log, Filter_T filter, int time, int id)
{
    int size = filter->n_filters;
    for (int i = 0; i < size; i++)
        Log_layer(log, filter->layers[i], time, id + ((i + 1) * 100));
}

void Log_print_head(Log_T log)
{
    fprintf(log, "a, b, c, d, e\n");
}

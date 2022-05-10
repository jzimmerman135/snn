#include "logger.h"
#include "string.h"

#define MAX_LINES 100000

Log_T Log_open(char *filename)
{
    /* add path to filename */
    Log_T log = malloc(sizeof(struct Log_T));
    char path[50] = "./analysis/output/";
    strcat(path, filename);
    filename = path;

    /* add modifiers before creating file */
    strcat(filename, ".out");

    log->fp = fopen(filename,"w");
    log->line_count = 0;
    log->time = 0;
    log->input_index = 0;

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

/* example id: 401 means filter 3 layer 1
    or     id: 2 means layer 2 outside of a filter
           id: a0b means filter a - 1, layer b
*/

void Log_layer(Log_T log, Layer_T layer, int id)
{
    if (++log->line_count > MAX_LINES) {
        if (log->line_count == MAX_LINES)
            fprintf(stderr, "Error: Max log lines exceeded, logging ended\n");
        else
            return;
    }

    fprintf(log->fp, "%i, %i, %i\n", Layer_size(layer), log->time, id);
}

void Log_filter(Log_T log, Filter_T filter, int id)
{
    int size = filter->n_filters;
    for (int i = 0; i < size; i++)
        Log_layer(log, filter->layers[i], id + ((i + 1) * 100));
}

void Log_print_head(Log_T log)
{
    fprintf(log->fp, "a, b, c, d, e\n");
}

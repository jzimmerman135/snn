#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include "layer.h"
#include "filter.h"
#include <stdio.h>

typedef struct Log_T *Log_T;
struct Log_T {
    FILE *fp;
    int line_count;
    int time;
    int input_index;
};

extern Log_T Log_open(char *filename);
extern void Log_close(Log_T *log);
extern void Log_layer(Log_T log, Layer_T layer, int id);
extern void Log_filter(Log_T log, Filter_T filter, int id);

#endif

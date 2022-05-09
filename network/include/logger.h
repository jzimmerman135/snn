#ifndef Log_INCLUDED
#define Log_INCLUDED

#include <stdio.h>
#include "layer.h"
#include "filter.h"

typedef FILE *Log_T;
extern Log_T Log_open(char *filename);
extern void Log_close(Log_T *log);
extern void Log_layer(Log_T log, Layer_T layer, int time, int id);
extern void Log_filter(Log_T log, Filter_T filter, int time, int id);

#endif

#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include "layer.h"

typedef struct Logger_T *Logger_T;

extern Logger_T Logger_new(char *filename);
extern void Logger_free(Logger_T *log);
extern void Logger_log(Logger_T log, Layer_T layer, int time, int id);

#endif

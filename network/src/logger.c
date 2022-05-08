#include "logger.h"
#include "stdio.h"
#include "string.h"

struct Logger_T {
    FILE *spike_fp;
    FILE *weights_fp;
    FILE *header_fp;
};

Logger_T Logger_new(char *filename)
{
    Logger_T log = malloc(sizeof(struct Logger_T));
    char spike_path[50], weights_path[50], head_path[50];

    strcpy(spike_path, "../analysis/output/");
    strcat(spike_path, filename);

    strcpy(weights_path, spike_path);
    strcpy(head_path, spike_path);

    strcat(spike_path, ".out");
    strcat(weights_path, "_w.out");
    strcat(head_path, "_h.out");

    log->spike_fp   = fopen(spike_path,"w");
    log->weights_fp = fopen(weights_path,"w");
    log->header_fp  = fopen(head_path,"w");

    return log;
}

void Logger_free(Logger_T *log)
{
    fclose((*log)->spike_fp);
    fclose((*log)->weights_fp);
    fclose((*log)->header_fp);

    free(*log);
}

void Logger_log(Logger_T log, Layer_T layer, int time, int id)
{
    (void)log, (void)layer, (void)time, (void)id;
}

#include "reader.h"

struct Reader_T {
    struct shape2_t input_shape;
    struct shape2_t label_shape;
    float **inputs;
    float **labels;
    int n_inputs;
    int n_input_channels;
    int n_label_channels;
};

Reader_T Reader_new(FILE *fp)
{
    Reader_T rdr = malloc(sizeof(struct Reader_T));

    int read;
    read = fscanf(fp, "%i INPUTS, %i INPUT CHANNELS, %i OUTPUT CHANNELS:",
                      &rdr->n_inputs,
                      &rdr->n_input_channels,
                      &rdr->n_label_channels);

    if (read != 3) {
        fprintf(stderr, "Error: could not read header\n");
        exit(1);
    }

    if (fgetc(fp) != 10) {
        fprintf(stderr, "Error: weird newline reading error\n");
        exit(1);
    }

    rdr->inputs = malloc(sizeof(float*) * rdr->n_inputs);
    rdr->labels = malloc(sizeof(float*) * rdr->n_inputs);

    for (int i = 0; i < rdr->n_inputs; i++) {
        rdr->inputs[i] = malloc(sizeof(float*) * rdr->n_input_channels);
        rdr->labels[i] = malloc(sizeof(float*) * rdr->n_label_channels);
    }

    for (int i = 0; i < rdr->n_inputs; i++)
        fread(rdr->inputs[i], sizeof(float), rdr->n_input_channels, fp);

    for (int i = 0; i < rdr->n_inputs; i++)
        fread(rdr->labels[i], sizeof(float), rdr->n_label_channels, fp);

    /* TODO: FIX ME */
    rdr->input_shape.x = rdr->n_input_channels;
    rdr->input_shape.y = 1;

    rdr->label_shape.x = rdr->n_label_channels;
    rdr->label_shape.y = 1;

    return rdr;
}

void Reader_free(Reader_T *rdr_pp)
{
    Reader_T rdr = *rdr_pp;
    for (int i = 0; i < rdr->n_inputs; i++) {
        free(rdr->inputs[i]);
        free(rdr->labels[i]);
    }

    free(rdr->inputs);
    free(rdr->labels);
    free(rdr);
}

int Reader_size(Reader_T rdr)
{
    return rdr->n_inputs;
}

int Reader_input_channels(Reader_T rdr)
{
    return rdr->n_input_channels;
}

int Reader_label_channels(Reader_T rdr)
{
    return rdr->n_label_channels;
}

shape2_t Reader_shape_input(Reader_T rdr)
{
    return &rdr->input_shape;
}

shape2_t Reader_shape_label(Reader_T rdr)
{
    return &rdr->label_shape;
}

float *Reader_input(Reader_T rdr, int i)
{
    return rdr->inputs[i];
}

float *Reader_label(Reader_T rdr, int i)
{
    return rdr->labels[i];
}

void Reader_print(Reader_T rdr, int i)
{
    float *input_data = Reader_input(rdr, i);
    float *label_data = Reader_label(rdr, i);

    printf("SAMPLE %i, INPUT DATA:\n[ ", i);
    for (int i = 0; i < rdr->n_input_channels; i++)
        printf("%.3f, ", input_data[i]);
    printf("\b\b ]\n");

    printf("SAMPLE %i, LABEL DATA:\n[ ", i);
    for (int i = 0; i < rdr->n_label_channels; i++)
        printf("%.3f, ", label_data[i]);
    printf("\b\b ]\n");
}

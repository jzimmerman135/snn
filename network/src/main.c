#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "encoder.h"
#include "filter.h"
#include "layer.h"

void check_usage(int argc);
Reader_T Reader_new_from_argv(char *argv);

int main(int argc, char **argv)
{
    check_usage(argc);
    Reader_T train_data = Reader_new_from_argv(argv[1]);
    Reader_T test_data  = Reader_new_from_argv(argv[2]);

    Reader_print(train_data, 0);
    Reader_print(test_data, 0);

    // int n_input_channels = Reader_input_channels(train_data);
    // shape2_t input_shape = Reader_input_shape(train_data);
    // Encoder_T encoder = Encoder_new(input_shape);
    //
    // float *input_raw = Reader_input(train_data, 0);
    // Encoder_set_current(encoder, input_raw);
    //
    // for (int i = 0; i < 200; i++) {
    //     printf("[ ");
    //     bit2_t synapses = Encoder_spikes(encoder);
    //     for (int j = 0; j < n_input_channels; j++) {
    //         printf("%i,", synapses->data[j]);
    //     }
    //     printf("\b ]\n");
    // }
    //
    // Encoder_free(&encoder);
    Reader_free(&train_data);
    Reader_free(&test_data);
}

Reader_T Reader_new_from_argv(char *argv)
{
    char filename[64] = "./datasets/";
    strcat(filename, argv);
    FILE* fp = fopen(filename, "r");
    if (!fp){
        fprintf(stderr, "Error: failed to open file %s\n", filename);
        exit(1);
    }

    Reader_T data = Reader_new(fp);
    fclose(fp);
    return data;
}

void check_usage(int argc)
{
    if (argc < 3) {
        fprintf(stderr, "Error: missing arguments from "
                        "./program [training.data] [testing.data]\n");
        exit(1);
    }
}

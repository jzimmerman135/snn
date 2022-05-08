#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "encoder.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Error: missing arguments from "
                        "./program [training.data] [testing.data]\n");
        exit(1);
    }

    /* prep filenames */
    char train_filename[64] = "./datasets/";
    char test_filename[64] = "./datasets/";
    strcat(train_filename, argv[1]);
    strcat(test_filename, argv[2]);

    FILE* train_file = fopen(train_filename, "r");
    FILE* test_file = fopen(test_filename, "r");
    if (!train_file){
        fprintf(stderr, "Error: failed to open train file %s\n", argv[1]);
        exit(1);
    }
    if (!test_file) {
        fprintf(stderr, "Error: failed to open test file %s\n", argv[2]);
        exit(1);
    }

    Reader_T train_data = Reader_new(train_file);
    Reader_T test_data  = Reader_new(test_file);

    Reader_print(train_data, 0);
    Reader_print(test_data, 0);

    int n_input_channels = Reader_input_channels(train_data);
    shape2_t input_shape = Reader_input_shape(train_data);
    Encoder_T encoder = Encoder_new(input_shape);

    float *input_raw = Reader_input(train_data, 0);
    Encoder_set_current(encoder, input_raw);

    for (int i = 0; i < 200; i++) {
        printf("[ ");
        bit2_t synapses = Encoder_spikes(encoder);
        for (int j = 0; j < n_input_channels; j++) {
            printf("%i,", synapses->data[j]);
        }
        printf("\b ]\n");
    }

    Encoder_free(&encoder);
    Reader_free(&train_data);
    Reader_free(&test_data);
    fclose(train_file);
    fclose(test_file);
}

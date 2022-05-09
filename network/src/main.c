#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "encoder.h"
#include "filter.h"
#include "layer.h"
#include "helpful.h"
#include "network.h"
#include "matrix.h"

/******************************************************************************
                    USE THIS TO DESIGN YOUR OWN NETWORK

                     remember: filters must come first
******************************************************************************/
void Network_build(Network_T network)
{
    struct shape2_t l1_shape = {5, 1};
    struct shape2_t l2_shape = {6, 1};

    Network_add_layer(network, &l1_shape);
    Network_add_layer(network, &l2_shape);
}


/* function declarations */
void Model_train(Network_T network, Reader_T train_data);
Reader_T Reader_new_from_argv(char *argv);

int main(int argc, char **argv)
{
    check_usage(argc);
    Reader_T train_data = Reader_new_from_argv(argv[1]);
    Reader_T test_data  = Reader_new_from_argv(argv[2]);
    Reader_print(train_data, 0);
    Reader_print(test_data, 0);

    shape2_t input_shape = Reader_shape_input(train_data);
    shape2_t label_shape = Reader_shape_label(train_data);
    Network_T network = Network_new(input_shape, label_shape);

    Network_build(network);

    Model_train(network, train_data);
    Model_train(network, test_data);

    Network_free(&network);
    Reader_free(&train_data);
    Reader_free(&test_data);
}

void Model_train(Network_T network, Reader_T train_data)
{
    shape2_t input_shape = Reader_shape_input(train_data);
    shape2_t label_shape = Reader_shape_label(train_data);
    int n_training_examples = Reader_size(train_data);

    n_training_examples = 0; // DUMMY NEVE CALL LOOP
    for (int i = 0; i < n_training_examples; i++) {
        fprintf(stderr, "I DID SOMETHING\n");

        struct float2_t input = { .x = input_shape->x,
                                  .y = input_shape->y,
                                  .data = Reader_input(train_data, i)};
        struct float2_t label = { .x = label_shape->x,
                                  .y = label_shape->y,
                                  .data = Reader_label(train_data, i)};

        Network_feed(network, &input, &label);
    }
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

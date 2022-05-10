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
#include "logger.h"

/******************************************************************************
                USE THIS TO FUNCTION TO DESIGN YOUR OWN NETWORK

                     remember: filters must come first

          first define layer size with a struct shape2_t => { x_dim, y_dim }
then define parameters with struct param =>  { initial_weight, init_w_variance,
                            potentation rate, depression rate, beta learn rate,
                            membrance threshold potential }

******************************************************************************/
void Network_build(Network_T network)
{
    struct shape2_t l1_shape = {5, 1};
    struct shape2_t l2_shape = {6, 1};
    struct param_t l1_param = { .w = 0.5, .w_var = 0.25,
                                .a_p = 0.16, .a_d = 0.02, .b = 1.0,
                                .thr = 8.02 };

    Network_add_layer(network, &l1_shape, &l1_param);
    Network_add_layer(network, &l2_shape, &l1_param);
}


/******************************************************************************
                         Non client stuff is below
******************************************************************************/

/* function declarations */
int check_usage(int argc);
void Model_train(Network_T network, Reader_T train_data, Log_T log);
Reader_T Reader_new_from_argv(char *argv);

int main(int argc, char **argv)
{
    int save_results = check_usage(argc);
    Reader_T train_data = Reader_new_from_argv(argv[1]);
    Reader_T test_data  = Reader_new_from_argv(argv[2]);
    Log_T log = NULL;
    if (save_results)
        log = Log_open(argv[3]);

    shape2_t input_shape = Reader_shape_input(train_data);
    shape2_t label_shape = Reader_shape_label(train_data);
    Network_T network = Network_new(input_shape, label_shape);

    Network_build(network);

    Model_train(network, train_data, log);

    Network_free(&network);
    Log_close(&log);
    Reader_free(&train_data);
    Reader_free(&test_data);
}

void Model_train(Network_T network, Reader_T train_data, Log_T log)
{
    shape2_t input_shape = Reader_shape_input(train_data);
    shape2_t label_shape = Reader_shape_label(train_data);
    int n_training_examples = Reader_size(train_data);

    struct float2_t input = { .x = input_shape->x, .y = input_shape->y, NULL};
    struct float2_t label = { .x = label_shape->x, .y = label_shape->y, NULL};

    for (int i = 0; i < n_training_examples; i++) {
        input.data = Reader_input(train_data, i);
        label.data = Reader_label(train_data, i);
        log->input_index = i;

        Network_feed(network, &input, &label, log);
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

int check_usage(int argc)
{
    if (argc < 3) {
        fprintf(stderr, "Error: missing arguments from "
                        "./program [training.data] [testing.data]\n");
        exit(1);
    }

    return argc == 4; /* return true if log */
}

#include <iostream>
#include <fstream>
#include "specs.h"
#include "layer.h"
#include "reader.h"
#include "helpful.h"
#include "pulser.h"
#include <time.h>
#include <stdio.h>

using namespace std;

const string datasets_path = "./datasets/";
const string output_path   = "./analysis/output/";

void initialize_inputs(int argc, char **argv);

int main(int argc, char **argv)
{
    initialize_inputs(argc, argv);

    cout << "hello" << endl;

    float num = 0x12345678;

    cout << num << endl;


    Reader train;
    Reader test;
    train.read_input_data(spec->data.train_filename);
    test.read_input_data(spec->data.test_filename);

    cout << "TRAINING: " << endl;

    for (int i = 0; i < train.n_elem(); i++)
        train.print_input(i);

    cout << "TESTING: " << endl;

    for (int i = 0; i < test.n_elem(); i++)
        test.print_input(i);

    /*

    Pulser encoder;
    encoder.set_current(train.input(1));

    int inputs = spec->data.input_channels;
    int rounds = spec->cycles.per_input;

    train.print_input(1);

    for (int j = 0; j < rounds; j++) {
        int *spike_train = encoder.spikes();
        for (int i = 0; i < inputs; i++) {
            cout << spike_train[i] << ",";
        }
        cout << endl;
    }

    */

    // for (int i = 0; i < train.n_elem(); i++)
    //     train.print_input(i);
    //
    // cout << train.input_channels() << endl;
    // cout << train.output_channels() << endl;
    // cout << train.n_elem() << endl;

    return 0;
}



/* finish initializing spec */
void initialize_inputs(int argc, char **argv)
{
    verify(argc >= 2, "add an input training data file");
    verify(argc >= 3, "add an input testing data file");
    if (argc == 4) {
        spec->recording.save = true;
        spec->recording.filename = output_path + argv[3];
    }

    spec->data.train_filename = datasets_path + argv[1];
    spec->data.test_filename = datasets_path + argv[2];
}

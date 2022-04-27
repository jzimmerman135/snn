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

int main(int argc, char *argv[]) {
    verify(argc >= 2, "add an input training data file");
    verify(argc >= 3, "add an input testing data file");
    if (argc == 4) {
        spec->recording.save = true;
        spec->recording.filename = output_path + argv[3];
    }


    spec->data.train_filename = datasets_path + argv[1];
    spec->data.test_filename = datasets_path + argv[2];

    Reader train;
    train.read_input_data(spec->data.train_filename);

    for (int i = 0; i < train.n_elem(); i++)
        train.print_input(i);

    cout << train.input_channels() << endl;
    cout << train.output_channels() << endl;
    cout << train.n_elem() << endl;

    return 0;
}

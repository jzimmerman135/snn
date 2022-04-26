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

SpecSheet config()
{
    s = new SpecSheet;

    LayerSpec l1, l2, l3;
    l1.n_neurons = 12;
    l1.initial_weights = 10;
    l1.initial_weights_variance = 0.05;
}

int main(int argc, char **argv) {

    verify(argc == 2, "add an input data file");

    string datasets_path = "./datasets/";
    Reader train;
    train.read_input_data(datasets_path + argv[1]);

    for (int i = 0; i < train.n_elem(); i++)
        train.print_input(i);

    cout << train.input_channels() << endl;
    cout << train.output_channels() << endl;
    cout << train.n_elem() << endl;

    return 0;
}

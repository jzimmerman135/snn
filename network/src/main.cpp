#include <iostream>
#include <fstream>
#include "specs.h"
#include "layer.h"
#include "reader.h"
#include "helpful.h"
#include <time.h>
#include <stdio.h>

using namespace std;

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

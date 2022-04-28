#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "specs.h"
#include "helpful.h"
#include "reader.h"
#include "pulser.h"

using namespace std;

const string datasets_path = "./datasets/";
const string output_path   = "./analysis/output/";
void fprint_array(FILE *fp, int *arr, int n_elem);

int main(int argc, char **argv)
{
    float tau_m = 0.8;

    if (argc == 2) {
        tau_m = strtof(argv[1], NULL);
    }

    Reader data;
    data.read_input_data(datasets_path + "strain.data");

    Pulser encoder;
    data.print_input(0);
    encoder.set_current(data.input(0));
    encoder.set_tau(tau_m);

    string output_file = output_path + "pulser.out";
    FILE *out = fopen(output_file.c_str(), "w");

    for (int i = 0; i < 1000; i++) {
        int *spike_train = encoder.spikes();
        fprint_array(out, spike_train, encoder.size());
    }

    fclose(out);

    return 0;
}

void fprint_array(FILE *fp, int *arr, int n_elem)
{
    for (int j = 0; j < n_elem; j++) {
        fprintf(fp, "%i,", arr[j]);
    }
    fprintf(fp, "\n");
}

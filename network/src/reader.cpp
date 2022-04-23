#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "reader.h"


using namespace std;

Reader::Reader()
{
    inputs = nullptr;
    labels = nullptr;

    counter = -1; /* first elem is 0 */
    n_inputs = 0;
    n_input_channels = 0;
    n_output_channels = 0;

    return;
}

Reader::~Reader()
{
    if (inputs != nullptr) {
        for (int i = 0; i < n_inputs; i++)
            delete [] inputs[i];
        delete [] inputs;
    }

    if (labels != nullptr) {
        for (int i = 0; i < n_inputs; i++)
            delete [] labels[i];
        delete [] labels;
    }

    return;
}

void Reader::read_input_data(std::string filename)
{
    FILE *fp = fopen(filename.c_str(), "r");
    if (!fp) {
        cerr << "\033[1mError\033[0m: ";
        cerr << "failed to open data file \'" << filename << "\'\n";
        exit(1);
    }

    fscanf(fp, "%i INPUTS, %i INPUT CHANNELS, %i OUTPUT CHANNELS:",
                &n_inputs, &n_input_channels, &n_output_channels);

    inputs = new float*[n_inputs];
    labels = new float*[n_inputs];

    for (int i = 0; i < n_inputs; i++) {
        inputs[i] = new float[n_input_channels];
        labels[i] = new float[n_output_channels];
    }

    /* TODO: Read data */

    return;
}

float *Reader::next_input()
{
    counter++;
    return inputs[counter];
}

float *Reader::current_label()
{
    return labels[counter];
}

int Reader::output_channels()
{
    return n_output_channels;
}

int Reader::input_channels()
{
    return n_input_channels;
}

void Reader::verify_line(std::string a, std::string b)
{
    if (a != b) {
        cerr << "\033[1mError\033[0m: " << "parsing data failed\n";
        cerr << "Expected: " << b << "\n";
        cerr << "Read:     " << a << "\n";
        exit(1);
    }
}

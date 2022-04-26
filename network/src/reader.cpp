#include <stdio.h>
#include <iostream>
#include "reader.h"
#include "helpful.h"

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
        fprintf(stderr, "\033[1mError\033[0m: ");
        fprintf(stderr, "failed to open data file \'%s\'\n", filename.c_str());
        exit(1);
    }
    std::string message = "failed to open data file \'" + filename + "\'";

    size_t read;
    read = fscanf(fp, "%i INPUTS, %i INPUT CHANNELS, %i OUTPUT CHANNELS:\n",
                        &n_inputs, &n_input_channels, &n_output_channels);
    if (read != 3) {
        fprintf(stderr, "\033[1mError\033[0m: ");
        fprintf(stderr, "failed to read data file header\n");
        exit(1);
    }

    inputs = new float*[n_inputs];
    labels = new float*[n_inputs];

    for (int i = 0; i < n_inputs; i++) {
        inputs[i] = new float[n_input_channels];
        labels[i] = new float[n_output_channels];
    }

    for (int i = 0; i < n_inputs; i++)
        fread(inputs[i], sizeof(float), n_input_channels, fp);

    for (int i = 0; i < n_inputs; i++)
        fread(labels[i], sizeof(float), n_output_channels, fp);

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

void Reader::print_input(int i)
{
    printf("Input %i data is:\n", i);
    for (int j = 0; j < n_input_channels; j++)
        printf("%.3f ", inputs[i][j]);
    printf("\n");

    printf("Label %i data is:\n", i);
    for (int j = 0; j < n_output_channels; j++)
        printf("%.3f ", labels[i][j]);
    printf("\n");
}

int Reader::output_channels()
{
    return n_output_channels;
}

int Reader::input_channels()
{
    return n_input_channels;
}

int Reader::n_elem()
{
    return n_inputs;
}

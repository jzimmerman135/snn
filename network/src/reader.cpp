#include <stdio.h>
#include <iostream>
#include "reader.h"
#include "helpful.h"
#include "specs.h"

using namespace std;

Reader::Reader()
{
    inputs = nullptr;
    labels = nullptr;

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
    read = fscanf(fp, "%i INPUTS, %i INPUT CHANNELS, %i OUTPUT CHANNELS:",
                        &n_inputs, &n_input_channels, &n_output_channels);
    verify(read == 3, "failed to read data file header");

    verify(fgetc(fp) == 10, "if this happens weird problem. Tell Jacob pls");

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

    spec->data.input_channels = n_input_channels;
    spec->data.label_channels = n_output_channels;

    return;
}

float *Reader::input(int i)
{
    return inputs[i];
}

float *Reader::label(int i)
{
    return labels[i];
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

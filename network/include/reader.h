#ifndef READER_INCLUDED
#define READER_INCLUDED

#include <iostream>
#include "specs.h"

class Reader {
public:
    Reader();
    ~Reader();

    /* setters */

    void read_input_data(std::string filename);

    /* getters */

    float *input(int i);
    float *label(int i);
    void print_input(int i);

    int input_channels();
    int output_channels();
    int n_elem();
private:
    int n_input_channels;
    int n_output_channels;

    float **inputs;
    float **labels;
    int   n_inputs;
};

#endif

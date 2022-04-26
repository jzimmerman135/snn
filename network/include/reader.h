#ifndef READER_INCLUDED
#define READER_INCLUDED

#include <iostream>
#include "specs.h"

class Reader {
public:
    Reader();
    ~Reader();

    void read_input_data(std::string filename);

    float *next_input();
    float *current_label();

    int input_channels();
    int output_channels();
    int n_elem();

    void print_input(int i);
private:
    int counter;

    int n_input_channels;
    int n_output_channels;

    float **inputs;
    float **labels;
    int   n_inputs;
};

#endif

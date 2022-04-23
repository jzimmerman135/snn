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

private:
    int counter;

    int n_input_channels;
    int n_output_channels;

    float **inputs;
    float **labels;
    int   n_inputs;

    void verify_line(std::string a, std::string b);
};

#endif

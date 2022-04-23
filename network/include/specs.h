#ifndef SPECS_INCLUDED
#define SPECS_INCLUDED

#include <iostream>

class SpecSheet {
public:
    SpecSheet();
    ~SpecSheet();

    int n_layers;

    int n_input_channels; /* set by reader unit */
    int n_output_channels; /* set by reader unit */

    int *architecture;
    float *initial_weights;
    float *initial_weights_variance;
    float *v_thresholds;
    float *stdp_thresholds;

    float learn_beta;
    float learn_alpha;

    int cycles_per_input;
    int cycles_through_data;

    bool save_data;
    std::string output_filename;
    std::string train_data_filename;
    std::string test_data_filename;

private:
    void verify_line(std::string a, std::string b);
    void verify_reading(std::string a, std::string b, bool x);
};

#endif

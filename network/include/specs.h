#ifndef SPECS_INCLUDED
#define SPECS_INCLUDED

#include <iostream>

class SpecSheet {
public:
    SpecSheet();
    ~SpecSheet();

    int n_layers;

    int *architecture;
    float *initial_weights;
    float *initial_weights_variance;
    float *v_thresholds;
    float *stdp_thresholds;

    float learn_potentiation;
    float learn_depression;
    float learn_beta;

    int cycles_per_input;
    int cycles_through_data;

    int n_input_channels;       /* set by reader unit */
    int n_output_channels;      /* set by reader unit */

    bool save_data;                  /* set by main */
    std::string output_filename;     /* set by main */
    std::string train_data_filename; /* set by main */
    std::string test_data_filename;  /* set by main */

private:
    void verify_line(std::string a, std::string b);
    void verify_reading(std::string a, std::string b, bool x);
};

#endif

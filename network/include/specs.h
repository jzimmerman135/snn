#ifndef SPECS_INCLUDED
#define SPECS_INCLUDED

#include <iostream>

struct InitWeightSpec {
    float initial;
    float variance;
};

struct ConnectedLayerSpec {
    int   n_neurons;
    InitWeightSpec weights;
    float v_threshold;
    float stdp_threshold;
};

struct ConvolutionLayerSpec {
    int n_filter_neurons;
    int n_filters;
    int stride;
    int pooling_ratio;
    int inh_radius;
    float initial_weights;
    float initial_weights_variance;
    float v_threshold;
    float stdp_threshold;
};

struct ArchitectureSpec {
    int n_cv;
    int n_fc;
    int n_total;
    ConvolutionLayerSpec *cv_layers;
    ConnectedLayerSpec   *fc_layers;
};

struct RuntimeSpec {
    int per_input;
    int through_data;
};

struct LearningSpec {
    float potentiation;
    float depression;
    float beta;
};

struct InputDataSpec {
    int input_channels;
    int label_channels;
    std::string train_filename;
    std::string test_filename;
};

struct RuntimeDataSpec {
    bool save;
    std::string filename;
};

struct SpecSheet {
    ArchitectureSpec arch;
    LearningSpec learn;
    RuntimeSpec cycles;
    InputDataSpec data;
    RuntimeDataSpec recording;

    bool good();
};

// defined in config.cpp
extern SpecSheet *spec;

#endif

#include <iostream>
#include "./include/specs.h"
using namespace std;

/******************************************************************************

                            BUILD THE NETWORK

                    this symbol means user must define:  <====

******************************************************************************/

#define N_CV 0 // <==== number of convolutional layers and
#define N_FC 3 // <==== of fully connected layers

/* specify each layer's statistics */
static ConnectedLayerSpec l1 = { // <====
    .n_neurons = 20,
    .weights =  {
        .initial = 0.7,
        .variance = 0.05
    },
    .v_threshold = 8,
    .stdp_threshold = 8
};

static ConnectedLayerSpec l2 = { // <====
    .n_neurons = 40,
    .weights =  {
        .initial = 0.8,
        .variance = 0.05
    },
    .v_threshold = 8,
    .stdp_threshold = 8
};

static ConnectedLayerSpec l3 = { // <====
    .n_neurons = 60,
    .weights =  {
        .initial = 0.6,
        .variance = 0.4
    },
    .v_threshold = 12,
    .stdp_threshold = 12
};

/* fill the arrays with correct info */
/* if no cv_layers set to nullptr */
#if N_CV == 0
    static ConvolutionLayerSpec *cv_layers = nullptr;
#elif N_CV != 0
    static ConvolutionLayerSpec cv_layers[N_CV] = {}; // <====
#endif

static ConnectedLayerSpec   fc_layers[N_FC] = {l1, l2, l3}; // <====

static SpecSheet config = {
    /* customize this stuff below */
    .learn = {
        .potentiation = 0.8, // <====
        .depression = 0.1, // <==== (recommended 1/8th of potentiation)
        .beta = 0.3 // <====
    },

    .cycles = {
        .per_input = 1200, // <====
        .through_data = 2400 // <====
    },

    /* don't worry about this stuff below here */
    .arch = {
        .n_cv = N_CV,   // defined above
        .n_fc = N_FC,
        .n_total = N_CV + N_FC,
        .cv_layers = cv_layers,
        .fc_layers = fc_layers
    },

    .data = {
        .input_channels = 0, // automatically set
        .label_channels = 0,
        .train_filename = "",
        .test_filename = ""
    },

    .recording = {
        .save = false, // automatically set
        .filename = ""
    }
};

/* main export */
SpecSheet *spec = &config;

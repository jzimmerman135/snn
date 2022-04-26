#include <iostream>
#include <fstream>
#include <sstream>
#include "specs.h"
#include "helpful.h"

using namespace std;

SpecSheet::SpecSheet()
{
    /* these values must be set by clients of SpecSheet */
    save_data           = false;
    output_filename     = "";
    train_data_filename = "";
    test_data_filename  = "";
    n_input_channels    = 0;
    n_output_channels   = 0;

    architecture             = nullptr;
    initial_weights          = nullptr;
    initial_weights_variance = nullptr;
    v_thresholds             = nullptr;
    stdp_thresholds          = nullptr;
}

void SpecSheet::read_layers(LayerSpec *in_layers, int n_hidden_layers)
{
    for (int i = 0; i < n_hidden_layers; i++) {
        layers[i] = 
    }
}

void SpecSheet::read_config()
{
    // string line, parameter;
    // ifstream file;
    // stringstream ss;
    // file.open("config.snn");
    // verify(file.good(), "failed to open config.snn");
    //
    // getline(file, parameter);
    // verify_line(parameter, "SNN HYPER-PARAMETERS FILE");
    //
    // getline(file, parameter);
    // verify_line(parameter, "NUMBER OF HIDDEN LAYERS:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> n_layers);
    //
    // /* allocate arrays */
    // architecture = new int[n_layers];
    // initial_weights = new float[n_layers];
    // initial_weights_variance = new float[n_layers];
    // v_thresholds = new float[n_layers];
    // stdp_thresholds = new float[n_layers];
    //
    // /* parse the rest of the configuration */
    // getline(file, parameter);
    // verify_line(parameter, "CYCLES PER INPUT:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> cycles_per_input);
    //
    // getline(file, parameter);
    // verify_line(parameter, "CYCLES THROUGH DATA:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> cycles_through_data);
    //
    // getline(file, parameter);
    // verify_line(parameter, "NEURONS PER HIDDEN LAYER:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // for (int i = 0; i < n_layers; i++)
    //     verify_reading(parameter, line, ss >> architecture[i]);
    //
    // getline(file, parameter);
    // verify_line(parameter, "INITIAL WEIGHTS:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // for (int i = 0; i < n_layers; i++)
    //     verify_reading(parameter, line, ss >> initial_weights[i]);
    //
    // getline(file, parameter);
    // verify_line(parameter, "INITIAL WEIGHTS VARIANCE:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // for (int i = 0; i < n_layers; i++)
    //     verify_reading(parameter, line, ss >> initial_weights_variance[i]);
    //
    // getline(file, parameter);
    // verify_line(parameter, "MEMBRANE VOLTAGE THRESHOLDS:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // for (int i = 0; i < n_layers; i++)
    //     verify_reading(parameter, line, ss >> v_thresholds[i]);
    //
    // getline(file, parameter);
    // verify_line(parameter, "STDP THRESHOLDS:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // for (int i = 0; i < n_layers; i++)
    //     verify_reading(parameter, line, ss >> stdp_thresholds[i]);
    //
    // getline(file, parameter);
    // verify_line(parameter, "POTENTIATION LEARN RATE:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> learn_potentiation);
    //
    // getline(file, parameter);
    // verify_line(parameter, "DEPRESSION LEARN RATE:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> learn_depression);
    //
    // getline(file, parameter);
    // verify_line(parameter, "BETA LEARN RATE:");
    // getline(file, line);
    // ss.clear(), ss.str(line);
    // verify_reading(parameter, line, ss >> learn_beta);
    //
    // file.close();
}

SpecSheet::~SpecSheet()
{
    delete [] architecture;
    delete [] initial_weights;
    delete [] initial_weights_variance;
    delete [] v_thresholds;
    delete [] stdp_thresholds;
}

void SpecSheet::verify_line(string a, string b)
{
    if (a != b) {
        cerr << "\033[1mError\033[0m: " << "parsing config failed\n";
        cerr << "Expected: " << b << "\n";
        cerr << "Read:     " << a << "\n";
        exit(1);
    }
}

void SpecSheet::verify_reading(string a, string b, bool x)
{
    if (!x) {
        cerr << "\033[1mError\033[0m: " << "failed to read values in config\n";
        cerr << "Missing value in => " << a << " " << b << "\n";
        exit(1);
    }
}

#include "layer.h"
#include "network.h"
#include "pulse.h"
#include "reader.h"
#include "specs.h"
#include <iostream>

using namespace std;

// int main(int argc, char **argv) {
//     if (argc < 3) {
//         cerr << "Error: please provide training and testing .data files.\n";
//         exit(1);
//     }
//
//     SpecSheet specs;
//
//     specs.train_data_filename = argv[1];
//     specs.test_data_filename =  argv[2];
//
//     if (argc == 4) {
//         specs.save_data = true;
//         specs.output_filename = argv[3];
//     }
//
//     Network snn = Network(specs);
//     snn.train();
//     snn.test();
//
//     return 0;
// }

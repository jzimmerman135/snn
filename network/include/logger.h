#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include <iostream>
#include "layer.h"

class Logger {
friend class Layer;
public:
    Logger();
    bool save();
    void log(Layer layer, int time);
    void write();

private:
    bool save_requested;

    // std::string col_names[10];
    // std::vector<int> j;
    // std::vector<int> l;
    // std::vector<int> input;
    // std::vector<int> output;
    // std::vector<float> V;
    // std::vector<float> Vstdp;
    // std::vector<int> t;
    // std::vector<float> Wj;
    // std::vector<int> nprev;
    // std::vector<int> Linh;
};

#endif

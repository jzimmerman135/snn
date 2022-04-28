#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include <iostream>
#include <vector>
#include "layer.h"

class Logger {
public:
    Logger();
    ~Logger();

    bool save();
    void log(Layer layer, int time, int input_idx);
    void write();
private:
    bool save_requested;

    int count;

    std::string col_names[10];
    std::vector<int> j;
    std::vector<int> l;
    std::vector<int> input;
    std::vector<int> spike;
    std::vector<float> V;
    std::vector<float> Vstdp;
    std::vector<int> t;
    std::vector<float*> Wj;
    std::vector<int> nprev;
    std::vector<int> Linh;
};

#endif

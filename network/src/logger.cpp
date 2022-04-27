#include <iostream>
#include <fstream>
#include <vector>
#include "logger.h"

using namespace std;

Logger::Logger()
{
    save_requested = spec->recording.save;
}

bool Logger::save()
{
    return save_requested;
}

void Logger::write()
{
    if (!save_requested)
        return;

    cout << "writing data to " << spec->recording.filename << "\n";
    return;
}

void Logger::log(Layer layer, int time)
{
    (void)layer;
    (void)time;

    return;
}

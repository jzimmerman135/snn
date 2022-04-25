#include <iostream>
#include <fstream>
#include "specs.h"
#include "layer.h"
#include <time.h>
#include <stdio.h>

using namespace std;

int main() {
    cout << "hello world" << endl;
    srand(time(nullptr));

    for (size_t i = 0; i < 20; i++) {
        float r = 0.05 * (float)(rand() % 100) / 100.f;
        cout << r << endl;
    }
    string name = "demo";
    string fullname = "./analysis/output/" + name + ".out";

    ofstream file;
    file.open(fullname);

    if (!file.good())
        cout << "failed to open file\n";

    file << "Hello folder\n";

    SpecSheet specs;

    return 0;
}

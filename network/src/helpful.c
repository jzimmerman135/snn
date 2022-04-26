#include <iostream>
#include <stdio.h>
#include "helpful.h"

void verify(bool success_case, std::string message)
{
    if (!success_case) {
        cerr << "\033[1mError\033[0m: ";
        cerr << message << endl;
        exit(EXIT_FAILURE);
    }
}

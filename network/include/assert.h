#ifndef ASSERT_INCLUDED
#define ASSERT_INCLUDED
#include <stdlib.h>
#include <stdio.h>

#define assert(x) { \
    if (!(x)) { \
    fprintf(stderr, "Error: assertion failed at line %i, in file %s\n", __LINE__, __FILE__); \
    exit(1); } \
}

#endif

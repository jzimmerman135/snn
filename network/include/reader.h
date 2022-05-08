#ifndef READER_INCLUDED
#define READER_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "layer.h"

typedef struct Reader_T *Reader_T;
extern Reader_T Reader_new(FILE *fp);
extern void Reader_free(Reader_T *rdr);
extern int Reader_size(Reader_T rdr);
extern int Reader_input_channels(Reader_T rdr);
extern int Reader_label_channels(Reader_T rdr);
extern shape2_t Reader_shape_input(Reader_T rdr);
extern shape2_t Reader_shape_label(Reader_T rdr);
extern float *Reader_input(Reader_T rdr, int i);
extern float *Reader_label(Reader_T rdr, int i);
extern void Reader_print(Reader_T rdr, int i);

#endif

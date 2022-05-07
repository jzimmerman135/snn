#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <stdlib.h>

typedef struct Vec_T *Vec_T;
extern Vec_T Vec_new();
extern void Vec_free(Vec_T *vec);
extern void Vec_pushi(Vec_T vec, int elem);
extern void Vec_pushf(Vec_T vec, float elem);
extern void Vec_pushc(Vec_T vec, char elem);
extern void Vec_pushp(Vec_T vec, void *elem);
extern void *Vec_push(Vec_T vec); /* client casts and derefences */
extern void *Vec_at(Vec_T vec, int index);

#endif

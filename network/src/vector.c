#include "vector.h"
#include "assert.h"
#include <stdint.h>

#define INIT_SIZE 16

static void Vec_expand(Vec_T vec);

struct Vec_T {
    int size;
    int length;
    int capacity;
    char *elems;
};

Vec_T Vec_new(int size)
{
    Vec_T vec = malloc(sizeof(struct Vec_T));
    assert(vec);
    vec->size = size;
    vec->length = 0;
    vec->capacity = INIT_SIZE;
    vec->elems = malloc(size * INIT_SIZE);
    assert(vec->elems);
    return vec;
}

void Vec_free(Vec_T *vec)
{
    assert(*vec && vec);
    free((*vec)->elems);
    free(*vec);
}

void Vec_pushi(Vec_T vec, int elem)
{
    assert(vec->size == sizeof(int));
    if (vec->length == vec->capacity)
        Vec_expand(vec);

    *(int*)Vec_at(vec, vec->length) = elem;
    ++vec->length;
}

void Vec_pushf(Vec_T vec, float elem)
{
    assert(vec->size == sizeof(float));
    if (vec->length == vec->capacity)
        Vec_expand(vec);

    *(float*)Vec_at(vec, vec->length) = elem;
    ++vec->length;
}

void Vec_pushc(Vec_T vec, char elem)
{
    assert(vec->size == sizeof(float));
    if (vec->length == vec->capacity)
        Vec_expand(vec);

    *(char*)Vec_at(vec, vec->length) = elem;
    ++vec->length;
}

void Vec_pushp(Vec_T vec, void *elem)
{
    assert(vec->size == sizeof(void*));
    if (vec->length == vec->capacity)
        Vec_expand(vec);

    *(uintptr_t*)Vec_at(vec, vec->length) = (uintptr_t)elem;
    ++vec->length;
}

void *Vec_push(Vec_T vec)
{
    if (vec->length == vec->capacity)
        Vec_expand(vec);

    return Vec_at(vec, vec->length++);
}

void *Vec_at(Vec_T vec, int index)
{
    return vec->elems + index * vec->size;
}

static void Vec_expand(Vec_T vec)
{
    vec->capacity *= 2;
    vec->elems = realloc(vec->elems, vec->capacity * vec->size);
    assert(vec->elems);
}

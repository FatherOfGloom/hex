#ifndef VEC_H_
#define VEC_H_

#include "hex_utils.h"
#include <string.h>
#include <assert.h>

#define VEC_INIT_CAPACITY 256
#define VEC_GROWTH_MULTIPLIER 2

typedef struct Vec {
    void* items;
    usize len;
    usize capacity;
} Vec;

#define vec_is_empty(v) ((v)->len == 0)
#define vec_push(v, item_size, val) vec_append(v, item_size, val, 1);
#define vec_is_null(v) ((v)->items == NULL)


void vec_append(Vec* v, usize item_size, const void* new_items, usize count);
void vec_pop(Vec* v, usize item_size);
void vec_free(Vec* v);
err_t vec_try_realloc(Vec* v, usize item_size, usize new_v_cap);

#define VEC_INIT_CAPACITY 256
#define VEC_GROWTH_MULTIPLIER 2

#endif // VEC_H_
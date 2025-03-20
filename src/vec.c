#include "vec.h"

void vec_append(Vec* v, usize item_size, const void* new_items, usize count) {
    if (v->len + count > v->capacity) {
        if (v->capacity == 0) {
            v->capacity = VEC_INIT_CAPACITY;
        }

        while (v->len + count > v->capacity) {
            v->capacity *= VEC_GROWTH_MULTIPLIER;
        }

        v->items = realloc(v->items, v->capacity * item_size);
        assert(v->items != NULL && "unlucky peperony");
        discard memset(v->items + v->len, 0, (v->capacity - v->len) * item_size);
    }

    discard memcpy(v->items + v->len, new_items, count * item_size);
    v->len += count;
}

void vec_pop(Vec* v, usize item_size) {
    assert((v->len - item_size >= 0 || v->capacity == 0) && "cannot pop from an empty vec");
    assert((!vec_is_null(v)) && "cannot pop from a null vec");
    discard memset(v->items + v->len - item_size, 0, item_size);   
    v->len = v->len - item_size;
}

void vec_free(Vec* v) {
    if (v->items) {
        free(v->items);
    }

    v->items = NULL;
    v->len = 0;
    // we new to set capacity to 0 so that next append call will realloc the buffer;
    v->capacity = 0;
}

err_t vec_try_realloc(Vec* v, usize item_size, usize new_v_cap) {
    if (v->capacity >= new_v_cap) {
        return ERR;
    }

    v->capacity = new_v_cap;
    v->items = realloc(v->items, new_v_cap * item_size);
    assert(v->items && "unlucky peperony");
    discard memset(v->items + v->len, 0, (v->capacity - v->len) * item_size);

    return OK;
}
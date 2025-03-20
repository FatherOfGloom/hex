#include "str.h"

usize str_append(Str* s, const char* cstr) {
    usize len = strlen(cstr);

    // if we need to explicitly allocate a null character via str_append("");
    if (len == 0) {
        vec_append(&s->raw_str, sizeof(u8), "", 1);
        return len;
    }

    vec_append(&s->raw_str, sizeof(u8), cstr, len); 
    return len;
}

// Append a single byte to a string
void str_push(Str* s, char c) {
    vec_append(&s->raw_str, sizeof(u8), (char[]) { c, '\0' }, 1); 
}

// Allocate a dynamic string from a c string literal
Str str_from(const char* const cstr) {
    Str s = {0};

    if (str_append(&s, cstr) == 0) {
        // if we created a string from "" we want it to be considered empty but not null
        // so we set len to 0 because '\0' as the first byte is insignificant
        s.raw_str.len = 0;
    }

    return s;
}

// Returns a null terminating c string
char* str_to_cstr(Str* s) {
    // The buf is memset to 0 after each allocation, so it automatically ends with '\0'
    // the only edge case is when the len is equal to capacity
    if (str_len(s) >= str_cap(s)) {
        // we don't want to call str_push(s, '\0') because it will affect the len of the string
        // and if we try to reverse it with str_reverse(s) the null character will be moved to the first position in the given string
        discard str_try_realloc(s, str_cap(s) * VEC_GROWTH_MULTIPLIER);
    }

    return (char*)str_raw_ptr(s);
}

i32 str_is_whitespace(Str* s) {
    if (str_is_empty(s)) {
        return 0;
    }

    for (i32 i = 0; i < str_len(s); ++i) {
        if (str_to_cstr(s)[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

u8 str_at(Str* s, i32 i) {
    assert(s->raw_str.len != 0 && "cannot index an empty string");
    assert((i >= 0 && i < s->raw_str.len) && "index out of string bounds"); 
    assert(s->raw_str.items && "the target string is not initialized");

    return ((u8*)s->raw_str.items)[i];
}

void str_set_at(Str* s, i32 i, u8 val) {
    assert(s->raw_str.len != 0 && "cannot index an empty string");
    assert((i >= 0 && i < s->raw_str.len) && "index out of string bounds");
    assert(s->raw_str.items && "the target string is not initialized");

    *(((u8*)s->raw_str.items) + i) = val;
}

// Returns a separately allocated copy (a deep copy) of a given dynamic string
Str str_clone(Str* s) {
    return str_from(str_to_cstr(s));
}

void str_append_move(Str* dst, Str* src) {
    vec_append(&dst->raw_str, sizeof(u8), src->raw_str.items, src->raw_str.len);
    str_free(src);
}

void str_append_cpy(Str* dst, Str* src) {
    vec_append(&dst->raw_str, sizeof(u8), src->raw_str.items, src->raw_str.len);
}
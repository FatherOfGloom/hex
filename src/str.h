#ifndef STR_H_
#define STR_H_

#include "vec.h"

typedef struct Str {
    Vec raw_str;
} Str;

#define STR_FMT "%.*s"

#define str_len(s) ((s)->raw_str.len)
#define str_cap(s) ((s)->raw_str.capacity)
#define str_raw_ptr(s) ((s)->raw_str.items)
#define str_null_or_empty(s) ((s).v.len == 0 || (s).v.items == NULL)
#define str_try_realloc(s, new_cap) vec_try_realloc(&((s)->raw_str), sizeof(u8), (new_cap)) 
#define str_free(s) vec_free(&((s)->raw_str))
#define str_println(s) printf("%.*s\n", (i32)str_len((s)), str_to_cstr(s)) 
#define str_is_empty(s) vec_is_empty(&((s)->raw_str))
#define str_is_null(s) vec_is_null(&s->raw_str)

usize str_append(Str* s, const char* cstr);
void str_push(Str* s, char c);
Str str_from(const char* const cstr);
char* str_to_cstr(Str* s);

#endif // STR_H_
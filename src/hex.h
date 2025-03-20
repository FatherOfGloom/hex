#ifndef HEX_H_
#define HEX_H_

#include <gmp.h>
#include "str.h"
#include <ctype.h>
#include <stdio.h>

#define hex_print(...) printf("hex >> %s", __VA_ARGS__)
#define hex_print_stderr(...) fprintf(stderr, "hex >> %s", __VA_ARGS__)

typedef struct Slice {
    void* rawptr;
    usize size_bytes;
} Slice;

i32 is_valid_input(const Slice* s);
Str get_hex(const Slice* s);
void print_usage(void);
Slice slice_from_cstr(const char* const cstr);
    
#endif // HEX_H_
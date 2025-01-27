#ifndef HEX_H_
#define HEX_H_

#include <unholy.h>
#include <ctype.h>
#include <gmp.h>

typedef char* cstr_t;

#define hex_print(...) printf("hex >> %s", __VA_ARGS__)

bool check_integer_input(Str* s);
Str get_hex(Str* const s);
void print_usage(void);
    
#endif // HEX_H_
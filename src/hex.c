#include "hex.h"

Slice slice_from_cstr(const char* const cstr) {
    return (Slice) { .rawptr = (void*)cstr, .size_bytes = strlen(cstr) + 1 };
}

i32 is_valid_input(const Slice* input_cstr) {
    if (input_cstr->size_bytes - 1 <= 0) {
        return 0;
    }

    char c = *(char*)input_cstr->rawptr;

    if (c == '0') {
        hex_print("A valid number cannot start with a trailing zero\n");
        return 0;
    }

    if (c != '-' && !isdigit(c)) {
        printf("A valid number cannot start with a '%s'\n", (char[]) { c, '\0' });
        return 0;
    }

    for (i32 i = 1; i < input_cstr->size_bytes - 1; ++i) {
        char c = *((u8*)input_cstr->rawptr + i);

        if (!isdigit(c)) {
            return 0;
        }
    }

    return 1; 
}

Str get_hex(const Slice* cstr_slice) {
    Str result = str_from("0x");
    mpz_t mpz;

    mpz_init_set_str(mpz, (char*)cstr_slice->rawptr, 10);
    char* cstr = mpz_get_str(NULL, 16, mpz);

    discard str_append(&result, cstr);

defer:
    free(cstr);
    mpz_clear(mpz);
    return result;
}

void print_usage(void) {
    hex_print("Usage: hex [numeric-value]\n");
}
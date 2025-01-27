#include "hex.h"

bool check_integer_input(Str* s) {
    usize len = str_len(*s);

    if (len <= 0) {
        return false;
    }

    char first_c = str_at(s, 0);

    if (first_c == '0') {
        hex_print("A valid number cannot start with a trailing zero\n");
        return false;
    }

    if (first_c != '-' && !isdigit(first_c)) {
        printf("A valid number cannot start with a '%s'\n", (char[]) { first_c, '\0' });
        return false;
    }

    for (i32 i = 1; i < len; ++i) {
        char c = str_at(s, i);

        if (!isdigit(c)) {
            return false;
        }
    }

    return true; 
}

Str get_hex(Str* const s) {
    Str result = str_from("0x");
    mpz_t mpz;

    mpz_init_set_str(mpz, str_to_cstr(s), 10);
    cstr_t cstr = mpz_get_str(NULL, 16, mpz);

    discard str_append(&result, cstr);

defer:
    free(cstr);
    mpz_clear(mpz);
    return result;
}

void print_usage(void) {
    hex_print("Usage: hex [numeric-value]\n");
}
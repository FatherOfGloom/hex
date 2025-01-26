#include <stdio.h>
#include <unholy.h>
#include <ctype.h>
#include <gmp.h>

typedef char* cstr_t;

const char hex_table[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

#define hex_print(...) printf("hex >> %s", __VA_ARGS__)
    
bool check_integer_input(Str* s) {
    usize len = str_len(*s);

    if (len <= 0) {
        return false;
    }

    if (str_at(s, 0) == '0') {
        hex_print("A valid number cannot start with a trailing zero\n");
        return false;
    }

    for (i32 i = 0; i < len; ++i) {
        char c = str_at(s, i);

        if (!isdigit(c)) {
            return false;
        }
    }
    return true; 
}

Str get_hex(Str* const s) {
    Str result = str_from("0x");
    usize len = str_len(*s);
    mpz_t mpz;

    mpz_init_set_str(mpz, str_to_cstr(s), 10);
    cstr_t bin_cstr = mpz_get_str(NULL, 2, mpz);
    usize bin_cstr_len = strlen(bin_cstr);

    Str bin = {0};

    if (bin_cstr_len % 4 != 0) {
        u8 needed_zeroes = 4 - bin_cstr_len % 4;

        for (i32 i = 0; i < needed_zeroes; ++i) {
            str_push(&bin, '0');
        }
    }

    discard str_append(&bin, bin_cstr);

#ifdef DEBUG
    printf(bin_cstr);
    printf("\n");
    str_print(&bin);
    printf("\n");
#endif  // DEBUG

    usize bin_len = str_len(bin);

    assert(bin_len % 4 == 0 && "Invalid binary representation.");

    for (i32 i = 0; i < bin_len; i += 4) {
        u8 four_bits = 0;

        for (i32 bit = 0; bit < 4; ++bit) {
            if (str_at(&bin, i + bit) == '1') {
                four_bits |= (1 << 3 - bit);
            }
        }

#ifdef DEBUG
        printf("four_bits '%d'\n", (i32)four_bits);
#endif  // DEBUG

        str_push(&result, hex_table[four_bits]);
    }

defer:
    if (bin_cstr) free(bin_cstr);
    str_free(&bin);

    return result;
}

void print_usage(void) {
    todo(nameof(print_usage));
}

err_t main(i32 argc, cstr_t argv[]) {
    err_t result = OK;

    if (argc != 2) {
        puts("1");
        print_usage();
        return_defer(result);
    }

    Str input = str_from(argv[1]);

    if (str_len(input) == 0) {
        hex_print("Input cannot be empty\n");
        return_defer(ERR);
    }
    
    if (!check_integer_input(&input)) {
        hex_print("This input is not a valid number\n");
        return_defer(ERR);
    }

    Str hex_result = get_hex(&input);
    
    str_print(&hex_result);

defer:
#ifndef BUILD_RELEASE
    str_free(&input);
    str_free(&hex_result);
#endif

    return result;
}
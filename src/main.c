#include <stdio.h>
#include "hex.h"

err_t main(i32 argc, cstr_t argv[]) {
    err_t result = OK;
    Str input = {0};
    Str hex_result = {0};

    if (argc != 2) {
        print_usage();
        return_defer(result);
    }

    input = str_from(argv[1]);

    if (str_len(input) == 0) {
        hex_print("Input cannot be empty\n");
        return_defer(ERR);
    }
    
    if (!check_integer_input(&input)) {
        hex_print("This input is not a valid number\n");
        return_defer(ERR);
    }

    hex_result = get_hex(&input);
    
    str_print(&hex_result);
    printf("\n");

defer:
#ifndef BUILD_RELEASE
    str_free(&input);
    str_free(&hex_result);
#endif

    return result;
}
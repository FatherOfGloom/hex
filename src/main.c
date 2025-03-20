#include "hex.h"

i32 main(i32 argc, char* argv[]) {
    i32 result = 0;
    Str hex_result = {0};

    if (argc != 2) {
        print_usage();
        return_defer(result);
    }

    Slice input = slice_from_cstr(argv[1]);

    // note: -1 since '\0' counts, and if we call slice_from_cstr("") 
    // we'll get a slice of a cstring that contains a single null terminator
    if (input.size_bytes - 1 == 0) {
        hex_print("Input cannot be empty\n");
        return_defer(-1);
    }
    
    if (!is_valid_input(&input)) {
        hex_print("This input is not a valid number\n");
        return_defer(-1);
    }

    hex_result = get_hex(&input);
    
    str_println(&hex_result);
defer:
#ifndef BUILD_RELEASE
    str_free(&hex_result);
#endif

    return result;
}
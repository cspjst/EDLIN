
#include "STR/str_fixed.h"
#include <stddef.h>

int main() {
    str_fixed_t str;

    // Test successful conversion
    str_cstr(&str, "Testing\r\n");
    str_print(&str);
    str_int(&str, 12345, 10);
    str_print(&str);
    str_println();

    str_int(&str, -6789, 10);
    str_print(&str);
    str_println();

    str_int(&str, 255, 16);
    str_print(&str);
    str_println();

    // Test error cases
    str_error_t err = str_int(&str, 0xFFFF, 2);
    str_print(&str);
    str_println();
    if (err != STR_SUCCESS) {
        str_print_error(err);
    }

    err = str_int(NULL, 123, 10);
    if (err != STR_SUCCESS) {
        str_print_error(err);
    }

    return 0;
}

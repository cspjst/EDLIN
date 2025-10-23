#include "str_fixed.h"

str_size_t str_cstr(str_fixed_t* str, const char* cstr) {
    if (!str || !cstr) return 0;
    str_fixed_size_t len = 0;
    while (cstr[len] != '\0') {
        len++;
        if (len >= STR_FIXED_SIZE) return 0;
    }
    for (str_fixed_size_t i = 0; i < len; i++) {
        str->text[i] = cstr[i];
    }
    str->text[len] = '\0';
    str->size = len;
    return len;
}

str_size_t str_int(str_fixed_t* str, int n, int base) {
    if (!str || (base < 2 || base > 36)) return 0;
    str_fixed_size_t pos = 0;
    int is_negative = 0;
    unsigned int i;
    if (n < 0 && base == 10) {
        is_negative = 1;
        i = -n;
    } else {
        i = (unsigned int)n;
    }
    // Build string in reverse order directly into str->text
    do {
        unsigned int digit = un % base;
        if (pos >= STR_FIXED_SIZE - 1) return 0;
        str->text[pos++] = (digit < 10) ? '0' + digit : 'a' + digit - 10;
        i /= base;
    } while (i > 0);
    if (is_negative) {
        if (pos >= STR_FIXED_SIZE - 1) return 0;
        str->text[pos++] = '-';
    }
    str->size = pos;
    str_reverse(str);
    return pos;
}

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str) {
    if (!str || str->size == 0) return 0;
    int16_t result = dos_write_file(stream, str->text, str->size);
    if (result == -1 || result > STR_FIXED_SIZE) return 0;
    return (str_size_t)result;
}

str_size_t str_stdout(const str_fixed_t* str) {
    return str_write(STDOUT, str);
}

str_size_t str_stderr(const str_fixed_t* str) {
    return str_write(STDERR, str);
}

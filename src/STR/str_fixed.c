#include "str_fixed.h"

static const str_fixed_t str_error[] = {
    {"Success", 7, 0},
    {"Null", 4, 0},
    {"Overflow", 8, 0},
    {"Invalid", 7, 0},
    {"IO fail", 7 , 0},
    {"Empty", 5, 0},
    {"Invalid", 7, 0}
};

str_size_t str_cstr(str_fixed_t* str, const char* cstr) {
    if (!str) return STR_ERROR_NULL;
    if (!cstr) return STR_ERROR_INVALID_PTR;

    str_fixed_size_t len = 0;
    while (cstr[len] != '\0') {
        len++;
        if (len >= STR_FIXED_SIZE) return STR_ERROR_OVERFLOW;
    }
    for (str_fixed_size_t i = 0; i < len; i++) {
        str->text[i] = cstr[i];
    }
    str->text[len] = '\0';
    str->size = len;

    return STR_SUCCESS;
}

str_error_t str_int(str_fixed_t* str, int n, int base) {
    if (!str) return STR_ERROR_NULL;
    if (base < 2 || base > 36) return STR_ERROR_INVALID_BASE;

    char buffer[STR_FIXED_SIZE];
    int i = STR_FIXED_SIZE - 1;
    int is_negative = 0;
    unsigned int un;

    if (n < 0 && base == 10) {
        is_negative = 1;
        un = -n;
    } else {
        un = (unsigned int)n;
    }

    buffer[i--] = '\0';
    do {
        unsigned int digit = un % base;
        buffer[i--] = (digit < 10) ? '0' + digit : 'a' + digit - 10;
        un /= base;
    } while (un > 0 && i >= 0);

    if (un > 0) return STR_ERROR_OVERFLOW;

    if (is_negative) {
        if (i < 0) return STR_ERROR_OVERFLOW;
        buffer[i--] = '-';
    }

    char* src = &buffer[i + 1];
    str_fixed_size_t size = 0;
    while (size < STR_FIXED_SIZE - 1 && src[size] != '\0') {
        str->text[size] = src[size];
        size++;
    }

    if (size >= STR_FIXED_SIZE) return STR_ERROR_OVERFLOW;
    str->text[size] = '\0';
    str->size = size;

    return STR_SUCCESS;
}

str_error_t str_write(dos_file_handle_t stream, const str_fixed_t* str) {
    if (!str) return STR_ERROR_NULL;
    if (str->size == 0) return STR_SUCCESS;

    int16_t result = dos_write_file(stream, str->text, str->size);
    return (result == str->size) ? STR_SUCCESS : STR_ERROR_IO;
}

str_error_t str_stdout(const str_fixed_t* str) {
    return str_write()
}

str_error_t str_stderr(const str_fixed_t* str);

str_error_t str_prn(const str_fixed_t* str)

void str_print(const str_fixed_t* str) {
    str_fprint(1, str);  // stdout
}

void str_println() {
    dos_write_file(1, "\r\n", 2);
}

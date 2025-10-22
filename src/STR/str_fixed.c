#include "str_fixed.h"
#include "str_errors.h"

str_size_t str_cstr(str_fixed_t* str, const char* cstr) {
    if (!str || !cstr) return 0;

    str_fixed_size_t len = 0;
    while (cstr[len] != '\0') {
        len++;
        if (len >= STR_FIXED_SIZE) {
            str_errno = STR_ERROR_OVERFLOW;
            return 0;
        }
    }
    for (str_fixed_size_t i = 0; i < len; i++) {
        str->text[i] = cstr[i];
    }
    str->text[len] = '\0';
    str->size = len;
    
    str_errno = STR_SUCCESS;
    return len;
}

str_size_t str_int(str_fixed_t* str, int n, int base) {
    if (!str || (base < 2 || base > 36)) return 0;

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
    if (un > 0) {
        str_errno = STR_ERROR_OVERFLOW;
        return 0;
    }
    if (is_negative) {
        if (i < 0) {
            str_errno = STR_ERROR_OVERFLOW;
            return 0;
        }
        buffer[i--] = '-';
    }
    char* src = &buffer[i + 1];
    str_fixed_size_t size = 0;
    while (size < STR_FIXED_SIZE - 1 && src[size] != '\0') {
        str->text[size] = src[size];
        size++;
    }
    if (size >= STR_FIXED_SIZE) {
        str_errno = STR_ERROR_OVERFLOW;
        return 0;
    }
    str->text[size] = '\0';
    str->size = size;

    str_errno = STR_SUCCESS;
    return size;
}

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str) {
    if (!str) {
        str_errno = STR_ERROR_NULL;
        return 0;
    }
    if (str->size == 0) {
        str_errno = STR_SUCCESS;
        return 0;
    }
    int16_t result = dos_write_file(stream, str->text, str->size);
    
    if (result == -1) {
        str_errno = STR_ERROR_IO;
        return 0;
    }
    if (result > STR_FIXED_SIZE) {
        str_errno = STR_ERROR_OVERFLOW;
        return 0;
    }
    str_errno = STR_SUCCESS;
    return (str_size_t)result;
}

str_size_t str_stdout(const str_fixed_t* str) {
    return str_write(STDOUT, str);
}

str_size_t str_stderr(const str_fixed_t* str) {
    return str_write(STDERR, str);
}

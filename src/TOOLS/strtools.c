#include "strtools.h"

uint16_t cstr_length(const char* p) {
    uint16_t n = 0;
    while (*p++) n++;
    return n;
}

char* cstr_int_to_alpha(int value, char* buffer, int base) {
    if (base < 2 || base > 16 || !buffer) {
        if (buffer) *buffer = '\0';
        return buffer;
    }

    char* ptr = buffer;
    int is_negative = 0;

    // Handle negative only for base 10
    if (value < 0 && base == 10) {
        is_negative = 1;
        // Use unsigned to safely handle INT_MIN
        unsigned int uvalue = (unsigned int)-(value + 1) + 1;
        do {
            *ptr++ = "0123456789"[uvalue % base];
            uvalue /= base;
        } while (uvalue);
    } else {
        unsigned int uvalue = (unsigned int)value;
        do {
            *ptr++ = "0123456789ABCDEF"[uvalue % base];
            uvalue /= base;
        } while (uvalue);
    }
    if (is_negative) *ptr++ = '-';
    *ptr = '\0';
    // Reverse in place
    char* start = buffer;
    char* end = ptr - 1;
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }

    return buffer;
}

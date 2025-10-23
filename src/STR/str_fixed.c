#include "str_fixed.h"
#include <stddef.h>

str_fixed_t* str_cstr(str_fixed_t* str, const char* cstr) {
    if (!str || !cstr) return NULL;
    str_fixed_size_t len = 0;
    while (cstr[len] != '\0') {
        len++;
        if (len >= STR_FIXED_SIZE) return NULL;
    }
    for (str_fixed_size_t i = 0; i < len; i++) {
        str->text[i] = cstr[i];
    }
    str->text[len] = '\0';
    str->size = len;
    return str;
}

str_fixed_t* str_str(str_fixed_t* dest, const str_fixed_t* src) {
    if (!str || !cstr) return NULL;
    for (str_fixed_size_t i = 0; i < src->size; i++) dest->text[i] = src->text[i];
    dest->size = src->size;
    return dest;
}

str_fixed_t* str_int(str_fixed_t* str, int n, int base) {
    if (!str || (base < 2 || base > 36)) return NULL;
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
        if (pos >= STR_FIXED_SIZE - 1) return NULL;
        str->text[pos++] = '-';
    }
    str->size = pos;
    return str_reverse(str);
}

str_fixed_t* str_reverse(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    str_size_t start = 0;
    str_size_t end = str->size;
    while (start < end) {
        char temp = str->text[start];
        str->text[start] = str->text[end];
        str->text[end] = temp;
        start++;
        end--;
    }
    return str;
}

str_fixed_t* str_to_upper(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    for (str_fixed_size_t i = 0; i < str->size; i++) 
        if (str->text[i] >= 'a' && str->text[i] <= 'z') 
            str->text[i] &= ~0x20;  // Clear bit 5 to make uppercase
    return str;
}

str_fixed_t* str_to_lower(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    for (str_fixed_size_t i = 0; i < str->size; i++) 
        if (str->text[i] >= 'A' && str->text[i] <= 'Z') 
            str->text[i] |= 0x20;  // Set bit 5 to make lowercase
    return str;
}

str_fixed_t* str_trim_left(str_fixed_t* str, const char* trim_chars) {
    if (!str || !trim_chars || str->size == 0) return NULL;
    str_fixed_size_t trim_count = 0;
    // Find first character NOT in trim_chars using size
    while (trim_count < str->size) {
        const char* tc = trim_chars;
        int should_trim = 0;        
        // Check each trim char
        while (*tc != '\0') {
            if (str->text[trim_count] == *tc) {
                should_trim = 1;
                break;
            }
            tc++;
        }
        if (!should_trim) break;
        trim_count++;
    }
    
    if (trim_count > 0) {
        // Shift remaining characters left
        for (str_fixed_size_t i = 0; i < str->size - trim_count; i++) 
            str->text[i] = str->text[i + trim_count];
        str->size -= trim_count;
    }
    return str;
}

str_fixed_t* str_trim_right(str_fixed_t* str, const char* trim_chars) {
    if (!str || !trim_chars || str->size == 0) return NULL;
    str_fixed_size_t trim_count = 0;
    // Find last character NOT in trim_chars using size
    for (str_fixed_size_t i = str->size; i > 0; i--) {
        const char* tc = trim_chars;
        int should_trim = 0;
        while (*tc != '\0') {
            if (str->text[i - 1] == *tc) {
                should_trim = 1;
                break;
            }
            tc++;
        }     
        if (!should_trim) break;
        trim_count++;
    }
    if (trim_count > 0) str->size -= trim_count;
    return str;
}

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str) {
    if (!str || str->size == 0) return 0;
    int16_t result = dos_write_file(stream, str->text, str->size);
    if (result == -1 || result > STR_FIXED_SIZE) return 0;
    return (str_size_t)result;
}

str_size_t str_write_varargs(dos_file_handle_t stream, const str_fixed_t* first, ...) {
    va_list args;
    va_start(args, first);
    str_size_t count = str_write(stream, first);
    const str_fixed_t* next;
    while ((next = va_arg(args, const str_fixed_t*)) != NULL) count += str_write(stream, next);
    va_end(args);
    return count;
}

str_size_t str_read(dos_file_handle_t stream, str_fixed_t* str) {
    if (!str || str->size == 0) return 0;
    int16_t result = dos_read_file(stream, str->text, STR_FIXED_SIZE);
    if (result == -1 || result == 0) return 0;
    str->size = (str_size_t)result;
    return str->size;
}

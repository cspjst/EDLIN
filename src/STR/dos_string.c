#include "dos_string.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

typedef union {
    void* ptr;
    uint16_t parts[2];
} str_addr_t;

str_fixed_t* str_cstr(str_fixed_t* str, const char* cstr) {
    if (!str || !cstr) return NULL;
    str_size_t len;
    str->size = len = 0;
    while (cstr[len] != '\0') {
        len++;
        if (len >= STR_FIXED_SIZE) return NULL;
    }
    for (str_size_t i = 0; i < len; i++) {
        str->text[i] = cstr[i];
    }
    str->size = len;
    return str;
}

str_fixed_t* str_str(str_fixed_t* dst, const str_fixed_t* src) {
    if (!dst|| !src) return NULL;
    for (str_size_t i = 0; i < src->size; i++) dst->text[i] = src->text[i];
    dst->size = src->size;
    return dst;
}

str_fixed_t* str_int(str_fixed_t* str, int32_t n, int base) {
    if (!str || (base < 2 || base > 36)) return NULL;
    str_size_t pos = 0;
    int is_negative = 0;
    uint32_t i;
    if (n < 0 && base == 10) {
        is_negative = 1;
        i = -n;
    } else {
        i = (uint32_t)n;
    }
    // Build string in reverse order directly into str->text
    do {
        uint32_t digit = i % base;
        if (pos >= STR_FIXED_SIZE - 1) return 0;
        str->text[pos++] = (digit < 10) ? '0' + digit : 'A' + digit - 10;
        i /= base;
    } while (i > 0);
    if (is_negative) {
        if (pos >= STR_FIXED_SIZE - 1) return NULL;
        str->text[pos++] = '-';
    }
    str->size = pos;
    return str_reverse(str);
}

str_fixed_t* str_bin(str_fixed_t* str, uint32_t num) {
    if (!str) return NULL;
    // Calculate needed nybbles (minimum 4 for 16 bits)
    uint8_t nybbles = 8;  // Start with max for 32-bit
    while (nybbles > 4 && (num >> (nybbles * 4 - 4)) == 0) {
        nybbles--;  // Reduce but stop at 4 nybbles (16 bits)
    }
    str_size_t pos = 0;
    // Convert each nybble
    for (int i = nybbles - 1; i >= 0; i--) {
        uint8_t nybble = (num >> (i * 4)) & 0x0F;

        // Convert nybble to binary (4 digits)
        for (int j = 3; j >= 0; j--) {
            str->text[pos++] = (nybble & (1 << j)) ? '1' : '0';
        }

        // Add space between nybbles (except after last one)
        if (i > 0) {
            str->text[pos++] = ' ';
        }
    }
    str->size = pos;
    return str;
}

str_fixed_t* str_hex(str_fixed_t* str, int32_t num) {
    if (!str) return NULL;
    str_size_t pos = 0;
    uint32_t value;
    uint8_t nybbles;
    // Handle negative numbers
    if (num < 0) {
        value = (uint32_t)num;  // Use full 32-bit 2's complement
        nybbles = 8;            // Always show 32-bit for negatives
    } else {
        // Positive - pad to 16 bits minimum
        value = num;
        nybbles = (num > 0xFFFF) ? 8 : 4;  // 32-bit if >16 bits, else 16-bit
    }
    // Convert each nybble
    for (int i = nybbles - 1; i >= 0; i--) {
        uint8_t nybble = (value >> (i * 4)) & 0x0F;
        str->text[pos++] = (nybble < 10) ? '0' + nybble : 'A' + nybble - 10;
        // Add space for 32-bit between words
        if (nybbles == 8 && i == 4) {
            str->text[pos++] = ' ';
        }
    }
    str->size = pos;
    return str;
}

str_fixed_t* str_ptr(str_fixed_t* str, void* p) {
    if (!str) return NULL;
    str_addr_t addr;
    addr.ptr = p;
    str_hex(str, addr.parts[1]);
    str_append_char(str, ':');
    str_append_str(str, as_hex(addr.parts[0]));
    return str;
}

str_fixed_t* str_reverse(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    str_size_t start = 0;
    str_size_t end = str->size - 1;
    while (start < end) {
        char temp = str->text[start];
        str->text[start] = str->text[end];
        str->text[end] = temp;
        start++;
        end--;
    }
    return str;
}

str_fixed_t* str_upper(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    for (str_size_t i = 0; i < str->size; i++)
        if (str->text[i] >= 'a' && str->text[i] <= 'z')
            str->text[i] &= ~0x20;  // Clear bit 5 to make uppercase
    return str;
}

str_fixed_t* str_lower(str_fixed_t* str) {
    if (!str || str->size == 0) return NULL;
    for (str_size_t i = 0; i < str->size; i++)
        if (str->text[i] >= 'A' && str->text[i] <= 'Z')
            str->text[i] |= 0x20;  // Set bit 5 to make lowercase
    return str;
}

str_fixed_t* str_trim_left(str_fixed_t* str, const char* trim_chars) {
    if (!str || !trim_chars || str->size == 0) return NULL;
    str_size_t trim_count = 0;
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
        for (str_size_t i = 0; i < str->size - trim_count; i++)
            str->text[i] = str->text[i + trim_count];
        str->size -= trim_count;
    }
    return str;
}

str_fixed_t* str_trim_right(str_fixed_t* str, const char* trim_chars) {
    if (!str || !trim_chars || str->size == 0) return NULL;
    str_size_t trim_count = 0;
    // Find last character NOT in trim_chars using size
    for (str_size_t i = str->size; i > 0; i--) {
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

str_fixed_t* str_append_char(str_fixed_t* str, char c) {
    if (!str || str->size >= STR_FIXED_SIZE - 1) return NULL;
    str->text[str->size] = c;
    str->size++;
    return str;
}

str_fixed_t* str_append_str(str_fixed_t* dest, const str_fixed_t* src) {
    if (!dest || !src || dest->size + src->size >= STR_FIXED_SIZE) return NULL;
    for (str_size_t i = 0; i < src->size; i++) {
        dest->text[dest->size + i] = src->text[i];
    }
    dest->size += src->size;
    return dest;
}

str_fixed_t* str_append_cstr(str_fixed_t* str, const char* cstr) {
    if (!str || !cstr) return NULL;
    str_size_t cstr_len = 0;
    while (cstr[cstr_len] != '\0') {
        cstr_len++;
        if (str->size + cstr_len >= STR_FIXED_SIZE) return NULL;
    }

    for (str_size_t i = 0; i < cstr_len; i++) {
        str->text[str->size + i] = cstr[i];
    }
    str->size += cstr_len;
    return str;
}

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str) {
    if (!str || str->size == 0) return 0;
    uint16_t nbytes = str->size;
    dos_write_file(stream, str->text, &nbytes);
    if (nbytes > STR_FIXED_SIZE) return 0;
    return nbytes;
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
    if (!str) return 0;
    uint16_t nbytes = STR_FIXED_SIZE;
    dos_read_file(stream, str->text, &nbytes);
    str->size = nbytes;
    return str->size;
}

str_size_t char_in(str_fixed_t* str) {
    str->size = 0;
    uint16_t nbytes = 1;
    dos_read_file(DOS_STDIN_HANDLE, str->text, &nbytes); // flush buffer
    str->size = nbytes;
    return str->size;
}

str_size_t str_in(str_fixed_t* str) {
    uint16_t nbytes = STR_FIXED_SIZE;
    dos_read_file(DOS_STDIN_HANDLE, str->text, &nbytes);
    str->size = nbytes;
    return str->size + 1;
}

str_size_t str_in_prompt(const str_fixed_t* prompt, str_fixed_t* str) {
    str_size_t count = str_out(prompt);
    count += str_in(str);
    return count;
}

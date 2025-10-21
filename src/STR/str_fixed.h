// string type with a user defined fixed capacity <= 255 and variable size 
#ifndef STR_FIXED_H
#define STR_FIXED_H

#ifndef STR_FIXED_SIZE
  #error "STR_FIXED_SIZE is undefined!"
#endif

typedef uint8_t str_fixed_size_t;
typedef uint8_t str_error_t; 

typedef struct {
    char text[STR_FIXED_SIZE];  
    str_fixed_size_t size;
    uint8_t flags;
} str_fixed_t;

typedef enum {
    STR_SUCCESS = 0,
    STR_ERROR_NULL,
    STR_ERROR_OVERFLOW,
    STR_ERROR_INVALID_BASE,
    STR_ERROR_IO,
    STR_ERROR_EMPTY,
    STR_ERROR_INVALID_PTR
} str_error_t;

str_error_t str_fprint(dos_file_handle_t stream, str_fixed_t* str);

void str_print(str_fixed_t* str);

void str_println(str_fixed_t* str);

str_error_t str_itoa(int n, str_fixed_t* str, int base)

#endif

/*
str_error_t str_fprint(dos_file_handle_t stream, str_fixed_t* str) {
    if (!str) return STR_ERROR_NULL;
    if (str->size == 0) return STR_SUCCESS;
    
    int16_t result = dos_write_file(stream, str->text, str->size);
    return (result == str->size) ? STR_SUCCESS : STR_ERROR_IO;
}

void str_print(str_fixed_t* str) {
    str_fprint(1, str);  // stdout
}

void str_println(str_fixed_t* str) {
    str_fprint(1, str);
    dos_write_file(1, "\r\n", 2);
}

str_error_t str_itoa(int n, str_fixed_t* str, int base) {
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
    
    // Copy without memcpy
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

static const str_fixed_t ERROR_MESSAGES[] = {
    {"Success", 7, 0},
    {"Null pointer", 12, 0},
    {"Buffer overflow", 15, 0},
    {"Invalid number base", 19, 0},
    {"I/O error", 9, 0},
    {"Empty string", 12, 0},
    {"Invalid pointer", 15, 0}
};

void str_fprint_error(dos_file_handle_t stream, str_error_t err) {
    if (err >= 0 && err <= STR_ERROR_INVALID_PTR) {
        str_fprint(stream, &ERROR_MESSAGES[err]);
    } else {
        str_fixed_t unknown = {"Unknown error", 13, 0};
        str_fprint(stream, &unknown);
    }
}

void str_print_error(str_error_t err) {
    str_fprint_error(2, err);  // stderr
}

*/

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
*/

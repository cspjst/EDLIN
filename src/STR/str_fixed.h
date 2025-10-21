// string type with a user defined fixed capacity <= 255 and variable size
#ifndef STR_FIXED_H
#define STR_FIXED_H

#include "../DOS/dos_services_files.h"
#include <stdint.h>

#define  STR_FIXED_SIZE 253

#ifndef STR_FIXED_SIZE
  #error "STR_FIXED_SIZE is undefined!"
#endif

typedef uint8_t str_fixed_size_t;

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

str_error_t str_cstr(str_fixed_t* str, const char* cstr);

str_error_t str_int(str_fixed_t* str, int n, int base);

str_error_t str_write(dos_file_handle_t stream, const str_fixed_t* str);

str_error_t str_stdout(const str_fixed_t* str);

str_error_t str_stderr(const str_fixed_t* str);

str_error_t str_prn(const str_fixed_t* str);

#endif

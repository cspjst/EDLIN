// string type with a user defined fixed capacity <= 255 and variable size
#ifndef STR_FIXED_H
#define STR_FIXED_H

#include "str_constants.h"
#include "str_types.h" 
#include "../DOS/dos_services_files.h"
#include <stdint.h>

#ifndef STR_FIXED_SIZE
  #error "STR_FIXED_SIZE is undefined!"
#endif

static const str_fixed_t CRLF = {"\r\n", 0, 0};

str_size_t str_cstr(str_fixed_t* str, const char* cstr);

str_size_t str_int(str_fixed_t* str, int n, int base);

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str);

str_error_t str_stdout(const str_fixed_t* str);

str_error_t str_stderr(const str_fixed_t* str);

str_error_t str_prn(const str_fixed_t* str);

#endif

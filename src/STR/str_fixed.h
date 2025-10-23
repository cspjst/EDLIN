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
str_size_t str_str(str_fixed_t* dest, const str_fixed_t* src);
str_size_t str_int(str_fixed_t* str, int n, int base);

str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str);
str_size_t str_write_varargs(dos_file_handle_t stream, const str_fixed_t* first, ...)
str_size_t str_read(dos_file_handle_t stream, str_fixed_t* str);

// Macros
#define str_stdout(...) str_write_v(STDOUT, __VA_ARGS__, NULL)
#define str_stderr(...) str_write_v(STDERR, __VA_ARGS__, NULL)
#define str_stdin(str) str_read(STDIN, str)
//str_size_t str_prn(const str_fixed_t* str);
#define str_stdin_prompt(prompt, str) (str_stdout(prompt) + str_stdin(str))

str_size_t str_reverse(str_fixed_t* str);

//str_size_t str_append_char(str_fixed_t* str, char c);
//str_size_t str_append_str(str_fixed_t* dest, const str_fixed_t* src);
//str_size_t str_append_cstr(str_fixed_t* str, const char* cstr);

//int str_compare(const str_fixed_t* str1, const str_fixed_t* str2);

//str_size_t str_find_char(const str_fixed_t* str, char c);
//str_size_t str_find_str(const str_fixed_t* str, const str_fixed_t* substr);

str_size_t str_to_upper(str_fixed_t* str);
str_size_t str_to_lower(str_fixed_t* str);

str_size_t str_trim_left(str_fixed_t* str);
str_size_t str_trim_right(str_fixed_t* str);
str_size_t str_trim(str_fixed_t* str);

//str_size_t str_substr(str_fixed_t* dest, const str_fixed_t* src);

#endif

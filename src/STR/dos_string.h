// string type with a user defined fixed capacity <= 255 and variable size
#ifndef STR_FIXED_H
#define STR_FIXED_H

#include "dos_string_constants.h"
#include "dos_string_types.h"
#include "../DOS/dos_services_files_constants.h"
#include "../DOS/dos_services_files.h"
#include <stdint.h>
#include <stddef.h>

#ifndef STR_FIXED_SIZE
  #error "STR_FIXED_SIZE is undefined!"
#endif

static const str_fixed_t STR_CRLF = {"\r\n", 2, 0};
static const str_fixed_t* CRLF = &STR_CRLF;
static str_fixed_t __temp_str = {"", 0, 0};
static str_fixed_t __temp_num = {"", 0, 0};

str_fixed_t* str_cstr(str_fixed_t* str, const char* cstr);
str_fixed_t* str_str(str_fixed_t* dest, const str_fixed_t* src);
str_fixed_t* str_int(str_fixed_t* str, int32_t n, int base);
str_fixed_t* str_bin(str_fixed_t* str, uint32_t num);
str_fixed_t* str_hex(str_fixed_t* str, int32_t num);
str_fixed_t* str_ptr(str_fixed_t* str, void* p);

str_fixed_t* str_reverse(str_fixed_t* str);
str_fixed_t* str_upper(str_fixed_t* str);
str_fixed_t* str_lower(str_fixed_t* str);

str_fixed_t* str_trim_left(str_fixed_t* str, const char* trim_chars);
str_fixed_t* str_trim_right(str_fixed_t* str, const char* trim_chars);

str_fixed_t* str_append_char(str_fixed_t* str, char c);
str_fixed_t* str_append_str(str_fixed_t* dest, const str_fixed_t* src);
str_fixed_t* str_append_cstr(str_fixed_t* str, const char* cstr);
//str_fixed_t* str_find_char(const str_fixed_t* str, char c);
//str_fixed_t* str_find_str(const str_fixed_t* str, const str_fixed_t* substr);
//str_fixed_t* str_substr(str_fixed_t* dest, const str_fixed_t* src); str_append_char(str_fixed_t* str, char c);
//int str_compare(const str_fixed_t* str1, const str_fixed_t* str2);



str_size_t str_write(dos_file_handle_t stream, const str_fixed_t* str);
str_size_t str_write_varargs(dos_file_handle_t stream, const str_fixed_t* first, ...);
str_size_t str_read(dos_file_handle_t stream, str_fixed_t* str);

str_size_t char_in(str_fixed_t* str);
str_size_t str_in(str_fixed_t* str);
str_size_t str_in_prompt(const str_fixed_t* prompt, str_fixed_t* str);

// macros
#define str_out(...) str_write_varargs(DOS_STDOUT_HANDLE, __VA_ARGS__, NULL)
#define str_err(...) str_write_varargs(DOS_STDERR_HANDLE, __VA_ARGS__, NULL)
#define str_prn(...) str_write_varargs(DOS_PRN_HANDLE, __VA_ARGS__, NULL)
#define str_trim(str, trims) (str_trim_right(str_trim_left(str, trims), trims))

#define as_dec(num) str_int(&__temp_num, num, 10)
#define as_bin(num) str_bin(&__temp_num, num)
#define as_hex(num) str_hex(&__temp_num, num)
#define as_ptr(ptr) str_ptr(&__temp_num, ptr)

#define cstr(cstr) str_cstr(&__temp_str, cstr)
#define crlf_trim(str) str_trim_right(str, "\r\n");

#endif

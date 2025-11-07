#ifndef EDLIN_FILE_BUFFER_H
#define EDLIN_FILE_BUFFER_H

#include "../STR/dos_string.h"
#include "../DOS/dos_services_files.h"
#include "edlin_types.h"

typedef struct {
    dos_file_handle_t fhandle;
    char* begin
    char* pos;
    char* end;
} edlin_file_buffer_t;

edlin_file_buffer_t* edlin_new_file_buffer(dos_file_handle_t fhandle, char* mem_ptr, edlin_size_t capacity);

edlin_size_t edlin_file_buffer_load(edlin_file_buffer_t* fbuffer);

str_fixed_t* edlin_file_buffer_next_string(edlin_file_buffer_t* fbuffer, str_fixed_t* str);

#endif

#ifndef EDLIN_FILE_BUFFER_H
#define EDLIN_FILE_BUFFER_H

#include "../DOS/dos_services_files.h"
#include "edlin_types.h"

typedef struct {
    dos_file_handle_t fhandle;
    char* bytes;
    edlin_size_t capacity;
} edlin_file_buffer_t;

edlin_file_buffer_t* edlin_new_file_buffer(char* file_path, char* mem_ptr, edlin_size_t capacity);


#endif

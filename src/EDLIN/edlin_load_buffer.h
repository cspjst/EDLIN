#ifndef EDLIN_LOAD_BUFFER_H
#define EDLIN_LOAD_BUFFER_H

#include "../DOS/dos_services_files.h"
#include "edlin_types.h"

typedef struct {
    dos_file_handle_t fhandle;
    char* bytes;
    edlin_size_t capacity;
} edlin_load_buffer_t;

edlin_load_buffer_t* edlin_new_load_buffer(char* file_path, char* buffer, edlin_size_t capacity);


#endif

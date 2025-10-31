#include "edlin_load_buffer.h"
#include <stddef.h>

edlin_load_buffer_t* edlin_new_load_buffer(char* file_path, char* buffer, edlin_size_t capacity) {
    edlin_load_buffer_t* load_buffer;
    // 1. place the buffer struct in buffer as once used to load the file it can be freed along with the buffer itself
    load_buffer = (edlin_load_buffer_t*)buffer;
    buffer += sizeof(edlin_load_buffer_t);
    // 2. open the file
    load_buffer->fhandle = dos_open_file(file_path, ACCESS_READ_ONLY);
    if(!load_buffer->fhandle) return NULL;
    // 3. initialize
    load_buffer->bytes = buffer;
    load_buffer->capacity = capacity - sizeof(edlin_load_buffer_t);
    return load_buffer;
}

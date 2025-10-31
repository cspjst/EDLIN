#include "edlin_file_buffer.h"
#include <stddef.h>

edlin_file_buffer_t* edlin_new_file_buffer(char* file_path, char* mem_ptr, edlin_size_t capacity) {
    edlin_file_buffer_t* fbuffer;
    // 1. place the buffer struct in buffer as once used to load the file it can be freed along with the buffer itself
    fbuffer = (edlin_file_buffer_t*)mem_ptr;
    mem_ptr += sizeof(edlin_file_buffer_t);
    // 2. open the file
    fbuffer->fhandle = dos_open_file(file_path, ACCESS_READ_ONLY);
    if(!fbuffer->fhandle) return NULL;
    // 3. initialize
    fbuffer->bytes = mem_ptr;
    fbuffer->capacity = capacity - sizeof(edlin_file_buffer_t);
    return fbuffer;
}

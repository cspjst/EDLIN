#include "edlin_file_buffer.h"
#include "edlin_types.h"
#include <stddef.h>

edlin_file_buffer_t* edlin_new_file_buffer(dos_file_handle_t fhandle, char* mem_ptr, edlin_size_t capacity) {
    // 0. check preconditions
    if(
        !fhandle
        ||!mem_ptr
        ||!capacity
    ) return NULL;
    edlin_file_buffer_t* fbuffer;
    // 1. place the buffer struct in buffer as once used to load the file it can be freed along with the buffer itself
    fbuffer = (edlin_file_buffer_t*)mem_ptr;
    mem_ptr += sizeof(edlin_file_buffer_t);
    // 2. initialize struct
    fbuffer->fhandle = fhandle;
    fbuffer->bytes = mem_ptr;
    fbuffer->capacity = capacity - sizeof(edlin_file_buffer_t);
    return fbuffer;
}

edlin_size_t edlin_file_buffer_load(edlin_file_buffer_t* fbuffer) {
    if(!fbuffer) return 0;
    edlin_size_t nbytes = 0;
    // TODO error handling
    dos_read_file(fbuffer->fhandle, fbuffer->bytes, fbuffer->capacity, &nbytes);
    return nbytes 
}

str_fixed_t* edlin_file_buffer_next_string(edlin_file_buffer_t* fbuffer, str_fixed_t* str) {
    edlin_size_t size = 0;
    char* b = fbuffer->bytes;
    char* s = str->text;
    while(*b != '\r' && *b != '\n' && size < STR_FIXED_SIZE) {
        *s = *b;
        b++;
        s++;
        size++;
    }
    if(size == STR_FIXED_SIZE) str->flags |= STR_OVERSIZED;
    str->size = size;
    return str;
}

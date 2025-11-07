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
    fbuffer->begin = mem_ptr;
    fbuffer->pos = fbuffer->begin;
    fbuffer->capacity = capacity - sizeof(edlin_file_buffer_t);
    fbuffer->end = fbuffer->begin + fbuffer->capacity;
    return fbuffer;
}

edlin_size_t edlin_file_buffer_load(edlin_file_buffer_t* fbuffer) {
    if(!fbuffer) return 0;
    edlin_size_t nbytes;
    // TODO error handling
    dos_read_file(fbuffer->fhandle, fbuffer->capacity, fbuffer->begin, &nbytes);
    return nbytes;
}

str_fixed_t* edlin_file_buffer_next_string(edlin_file_buffer_t* fbuffer, str_fixed_t* str) {
    if(str->flag != STR_UNDEFINED) return NULL; 
    char* p = str->text;
    while(
        *fbuffer->pos != '\r' 
        && *fbuffer->pos != '\n' 
        && str->size < STR_FIXED_SIZE
    ) {
        *p = *fbuffer->pos;
        fbuffer->pos++;
        p++;
        str->size++;
    } 
    // if partial line do not set valid line flag so that caller can call load and return the same string 
    // TODO
    if(str->size == STR_FIXED_SIZE) str->flags |= STR_OVERSIZED;
    str->flags |= STR_VALID;
    return str;
}

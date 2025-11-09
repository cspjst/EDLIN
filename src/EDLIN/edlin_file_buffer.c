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
    fbuffer->pos = fbuffer->begin;          // reset the buffer
    if(dos_read_file(                       // load buffer from file
        fbuffer->fhandle,
        fbuffer->capacity,
        fbuffer->begin,
        &nbytes
    ) == 0) return nbytes;                  // successful read
    return 0;                               // EOF or error
}

str_fixed_t* edlin_file_buffer_next_string(edlin_file_buffer_t* fbuffer, str_fixed_t* str) {
    if(
        !str_test(str, STR_FLAG_POOLED)         // not pooled
        || !str_test(str, STR_FLAG_SEQUENCED)   // not sequenced
    ) return NULL;
    char* p = str->text;
    while(
        fbuffer->pos < fbuffer->end             // reached end of buffer
        && *fbuffer->pos != '\n'                // end of line
        && str->size < STR_FIXED_SIZE           // end of string
    ) {
        *p = *fbuffer->pos;                     // copy char to string
        fbuffer->pos++;                         // next buffer char
        p++;                                    // next string char
        str->size++;                            // string size
    }
    if(fbuffer->pos == fbuffer->end) return str;// partially filled
    if(str->size == STR_FIXED_SIZE) str_set(str, STR_FLAG_OVERSIZED);
    str_set(str, STR_FLAG_ALLOCATED);
    return str;
}

#include "edlin_document.h"
#include "edlin_line_pool.h"
#include "edlin_line_sequence.h"

edlin_document_t* edlin_new_document(mem_arena_t* arena, str_fixed_t* str) {
    if(!arena || !str) return NULL;
    // 0. pre-initialize zeros and nulls
    edlin_document_t* doc = {0};
    // 1. calculate space free after sequence and pool type structs
    mem_size_bytes_t capacity = arena->free_size - (sizeof(edlin_line_sequence_t) + sizeof(edlin_line_pool_t));
    // 2. calculate shared capacity between sequence and pool
    capacity /= (sizeof(str_fixed_t*) + sizeof(str_fixed_t));
    if(capacity < 4) return NULL;
    // 3. create sequence with full capacity
    doc->seq = edlin_new_line_sequence(arena, capacity);
    // 4. create pool with 75% capacity (as EDLIN did) 25% will be used for the load buffer
    capacity = (capacity / 4) * 3;
    doc->pool = edlin_new_line_pool(arena, capacity);
    // 5. initialise file buffer with remaining 25% 
    doc->fbuffer = arena->mem_arena_alloc(arena, capacity / 3);
    return doc;
}

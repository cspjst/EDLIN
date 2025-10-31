#include "edlin_document.h"
#include "edlin_line_pool.h"
#include "edlin_line_sequence.h"

edlin_document_t* edlin_new_document(mem_arena_t* arena, str_fixed_t* str) {
    // 1. calculate space free after sequence and pool type structs
    mem_size_bytes_t capacity = arena->remaining - (sizeof(edlin_line_sequence_t) + sizeof(edlin_line_pool_t));

    // 2. calculate shared capacity between sequence and pool
    capacity /= (sizeof(str_fixed_t*) + sizeof(str_fixed_t));
    // 3. create sequence with full capacity

    // 4. create pool with 75% capacity (as EDLIN did) 25% will be used for the load buffer

    return NULL;
}

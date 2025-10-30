#include "edlin_document.h"
#include "edlin_line_pool.h"
#include "edlin_line_sequence.h"

#include <stdio.h>

edlin_document_t* edlin_new_document(mem_arena_t* arena) {
    // 1. calculate space free after sequence and pool type structs
    printf("arena %lu\n", arena->remaining);
    printf("seq size %lu\n", sizeof(edlin_line_sequence_t));
    printf("pool size %lu\n", sizeof(edlin_line_pool_t));

    mem_size_bytes_t capacity = arena->remaining - (sizeof(edlin_line_sequence_t) + sizeof(edlin_line_pool_t));

    printf("capacity %lu\n", capacity);
    printf("str_fixed_t* size %lu\n", sizeof(str_fixed_t*));
    printf("str_fixed_t size %lu\n", sizeof(str_fixed_t));
    // 2. calculate shared capacity between sequence and pool
    capacity /= (sizeof(str_fixed_t*) + sizeof(str_fixed_t));
    // 3. create sequence with full capacity
    printf("shared capacity %lu\n", capacity);
    // 4. create pool with 75% capacity (as EDLIN did) 25% will be used for the load buffer

    return NULL;
}

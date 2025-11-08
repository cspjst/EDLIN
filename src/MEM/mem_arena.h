#ifndef MEM_ARENA_H
#define MEM_ARENA_H

#include "mem_types.h"
#include <stdint.h>

#pragma pack(1)
typedef struct { // 16bytes size ie 1 paragraph
    uint16_t segment;
    char* base;
    char* free_ptr;
    mem_size_bytes_t used_size;
    mem_size_bytes_t free_size;
    mem_size_bytes_t capacity;
} mem_arena_t;
#pragma pack()

// Construction
mem_arena_t* mem_new_arena(mem_size_paragraphs_t paragraphs);

// Destruction
void mem_free_arena(mem_arena_t* arena);

// Mutation operation
char* mem_arena_alloc(mem_arena_t* arena, mem_size_bytes_t bytes);

#endif

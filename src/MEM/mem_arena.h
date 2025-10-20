#ifndef MEM_ARENA_H
#define MEM_ARENA_H

#include "mem_types.h"
#include <stdint.h>

typedef struct {
    uint16_t segment;
    char* base;
    char* free_ptr;
    char* end;
} mem_arena_t;

mem_arena_t* mem_arena_create(mem_size_paragraphs_t paragraphs);

void mem_arena_destroy(mem_arena_t* arena);

void* mem_arena_alloc(mem_arena_t* arena, uint32_t size);

#endif

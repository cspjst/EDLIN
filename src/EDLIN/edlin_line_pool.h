#ifndef EDLIN_LINE_BUFFER_H
#define EDLIN_LINE_BUFFER_H

#include "../STR/dos_string.h"
#include "../MEM/mem_arena.h"
#include "edlin_types.h"

#pragma pack(1)
typedef struct {
    str_fixed_t* lines;
    str_fixed_t* next_free;
    str_fixed_t* last_line;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_pool_t;
#pragma pack()

// Construction
edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t capacity);

// Mutation operations
str_fixed_t* edlin_alloc_line(edlin_line_pool_t* pool);
str_fixed_t* edlin_free_line(edlin_line_pool_t* pool, str_fixed_t* line);

#endif

#ifndef EDLIN_LINE_BUFFER_H
#define EDLIN_LINE_BUFFER_H

#include "../STR/dos_string.h"
#include "../MEM/mem_arena.h"
#include "edlin_types.h"

typedef str_fixed_t edlin_line_t;

typedef struct {
    edlin_line_t* lines;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_pool_t;

edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t lines);

edlin_line_t* edlin_first_line(edlin_line_pool_t* pool);

edlin_line_t* edlin_last_line(edlin_line_pool_t* pool);

edlin_line_t* edlin_next_line(edlin_line_pool_t* pool);

edlin_line_t* edlin_delete_line(edlin_line_pool_t* pool, edlin_line_t* line);

#endif

#ifndef EDLIN_LINE_SEQUENCE_H
#define EDLIN_LINE_SEQUENCE_H

#include "../STR/dos_string.h"
#include "../MEM/mem_arena.h"
#include "edlin_types.h"

typedef struct {
    str_fixed_t* ptrs;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_sequence_t;

// Construction
edlin_line_sequence_t* edlin_new_line_sequence(mem_arena_t* arena, edlin_size_t capacity);

// Accessor
str_fixed_t* edlin_sequence_get(const edlin_line_sequence_t* sequence, edlin_size_t index);

// Mutation operations
str_fixed_t* edlin_sequence_append(edlin_line_sequence_t* sequence, str_fixed_t* str);
str_fixed_t* edlin_sequence_insert(edlin_line_sequence_t* sequence, edlin_size_t index, str_fixed_t* str);
str_fixed_t* edlin_sequence_remove(edlin_line_sequence_t* sequence, edlin_size_t index);

#endif

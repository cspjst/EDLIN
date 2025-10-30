#ifndef EDLIN_LINE_SEQUENCE_H
#define EDLIN_LINE_SEQUENCE_H

#include "../STR/dos_string.h"
#include "../MEM/mem_arena.h"
#include "edlin_types.h"

#pragma pack(1)
typedef struct {
    str_fixed_t** line_ptrs;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_sequence_t;
#pragma pack()

// Construction
edlin_line_sequence_t* edlin_new_line_sequence(mem_arena_t* arena, edlin_size_t capacity);

// Accessor
str_fixed_t* edlin_sequence_at(const edlin_line_sequence_t* seq, edlin_size_t index);

// Mutation operations
str_fixed_t* edlin_sequence_append(edlin_line_sequence_t* seq,str_fixed_t* ptr);
str_fixed_t* edlin_sequence_delete(edlin_line_sequence_t* seq, edlin_size_t index);
str_fixed_t* edlin_sequence_insert(edlin_line_sequence_t* seq, edlin_size_t index, str_fixed_t* ptr);

#endif

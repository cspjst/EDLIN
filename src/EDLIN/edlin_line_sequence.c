#include "edlin_line_sequence.h"
#include <stddef.h>

edlin_line_sequence_t* edlin_new_line_sequence(mem_arena_t* arena, edlin_size_t max_lines) {
    // 1. allocate the sequence within the arena
    edlin_line_sequence_t* seq = (edlin_line_sequence_t*)mem_arena_alloc(arena, sizeof(edlin_line_sequence_t));
    if(!seq) return NULL;
    // 2. allocate the array of ptrs to str_fixed_t lines
    seq->line_ptrs = (str_fixed_t**)mem_arena_alloc(arena, max_lines * sizeof(str_fixed_t*));
    if (!seq->line_ptrs) return NULL;
    // 3. nullify all the ptrs
    for(str_size_t i = 0; i < max_lines; i++) seq->line_ptrs[i] = NULL;
    // 4. set up pool management pointers and counters
    seq->size = 0;                     // no lines allocated yet
    seq->capacity = max_lines;         // maximum lines this pool can hold
    return seq;  // ready for line allocation via edlin_alloc_line()
}

str_fixed_t* edlin_sequence_at(const edlin_line_sequence_t* seq, edlin_size_t index) {
    return seq->line_ptrs[index];
}

// Mutation operations
str_fixed_t* edlin_sequence_move(edlin_line_sequence_t* seq, edlin_size_t src, edlin_size_t dst, edlin_size_t size) {
    if( !seq
        || !size
        || dst == src
        || dst + size >= seq->capacity
    ) return NULL;
    while(size) {
        seq->line_ptrs[dst++] = seq->line_ptrs[src];
        seq->line_ptrs[src++] = NULL;
    }
}

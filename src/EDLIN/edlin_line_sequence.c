#include "edlin_line_sequence.h"
#include "edlin_types.h"
#include "edlin_constants.h"
#include <stddef.h>

edlin_line_sequence_t* edlin_new_line_sequence(mem_arena_t* arena, edlin_size_t capacity) {
    // 1. allocate the sequence within the arena
    edlin_line_sequence_t* seq = (edlin_line_sequence_t*)mem_arena_alloc(arena, sizeof(edlin_line_sequence_t));
    if(!seq) return NULL;
    // 2. allocate the array of ptrs to str_fixed_t lines
    seq->line_ptrs = (str_fixed_t**)mem_arena_alloc(arena, capacity * sizeof(str_fixed_t*));
    if (!seq->line_ptrs) return NULL;
    // 3. nullify all the ptrs
    for(edlin_size_t i = 0; i < capacity; i++) seq->line_ptrs[i] = NULL;
    // 4. set up pool management pointers and counters
    seq->size = 0;                     // no lines allocated yet
    seq->capacity = capacity;         // maximum lines this pool can hold
    return seq;  // ready for line allocation via edlin_alloc_line()
}

str_fixed_t* edlin_sequence_at(const edlin_line_sequence_t* seq, edlin_size_t index) {
    if(
        !seq                            // null sequence error
        || index >= seq->size           // index out of bounds error
    ) return NULL;
    return seq->line_ptrs[index];
}

// Mutation operations
str_fixed_t* edlin_sequence_append(edlin_line_sequence_t* seq,str_fixed_t* str) {
    if(
        !seq                            // null sequence error
        || !str                         // null ptr error
        || seq->size >= seq->capacity   // sequence full
        || str->flags == STR_UNDEFINED  // string must be valid
        || str_flag_test(str, STR_FLAG_SEQUENCED) // already in the sequence
    ) return NULL;
    seq->line_ptrs[seq->size++] = str;
    str_flag_set(str, STR_FLAG_SEQUENCED);
    return str;
}

str_fixed_t* edlin_sequence_insert(edlin_line_sequence_t* seq, edlin_size_t index, str_fixed_t* str) {
    if(
        !seq                            // null sequence error
        || !str                         // null ptr error
        || seq->size >= seq->capacity   // sequence full
        || index > seq->size            // index out of bounds error
        || str->flags == STR_UNDEFINED  // string must be valid
        || str_flag_test(str, STR_FLAG_SEQUENCED) // already in the sequence
    )  return NULL;
    // 1. ripple right any line ptrs to make space for the insertee
    for(edlin_size_t i = seq->size; i > index; i--) {
        seq->line_ptrs[i] = seq->line_ptrs[i-1];
    }
    // 2. insert the new ptr
    seq->line_ptrs[index] = str;
    seq->size++;
    str_flag_set(str, STR_FLAG_SEQUENCED);
    return str;
}

str_fixed_t* edlin_sequence_remove(edlin_line_sequence_t* seq, edlin_size_t index) {
    if(
        !seq                            // null sequence error
        || index >= seq->size           // index out of bounds error
    ) return NULL;
    // 1. save a copy then nullify the deletee
    str_fixed_t* p = seq->line_ptrs[index];
    seq->line_ptrs[index] = NULL;
    seq->size--;
    // 2. ripple left any line ptrs to right of the deletee
    while(index < seq->size) {
        seq->line_ptrs[index] = seq->line_ptrs[index + 1];
        seq->line_ptrs[index + 1] = NULL;
        index++;
    }
    str_flag_clr(p, STR_FLAG_SEQUENCED);
    return p;
}

void edlin_sequence_remove_all(edlin_line_sequence_t* seq) {
    while(seq->size) {
        edlin_sequence_remove(seq, seq->size - 1);
    }
}

#ifndef EDLIN_DOCUMENT_H
#define EDLIN_DOCUMENT_H

#include "../STR/str_fixed.h"
#include "../MEM/mem_arena.h"
#include "edlin_line_pool.h"
#include "edlin_line_sequence.h"
#include "edlin_file_buffer.h"
#include "edlin_types.h"

#pragma pack(1)
typedef struct {
    edlin_line_pool_t* pool;
    edlin_line_sequence_t* seq;
    edlin_file_buffer_t* fbuffer;
    edlin_size_t curr_line;
    uint8_t is_binary;
    uint8_t is_saved;
} edlin_document_t;
#pragma pack()

// Construction
edlin_document_t* edlin_new_document(mem_arena_t* arena, str_fixed_t* str);

#endif

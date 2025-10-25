#ifndef EDLIN_LINE_BUFFER_H
#define EDLIN_LINE_BUFFER_H

#include "../STR/str_fixed.h"
#include "edlin_types.h"

typedef struct {
    str_fixed_t* lines;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_pool_t;

edlin_line_pool_t* edlin_new_line_pool(edlin_size_t capacity);

//void edlin_free_line_pool(edlin_line_ppol_t* pool); // not needed if using mem_arena

#endif

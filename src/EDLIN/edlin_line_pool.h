#ifndef EDLIN_LINE_BUFFER_H
#define EDLIN_LINE_BUFFER_H

#include "../STR/str_fixed.h"
#include "edlin_types.h"

typedef struct {
    str_fixed_t* lines;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_pool_t

#endif

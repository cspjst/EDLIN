#ifndef EDLIN_LINE_MAP_H
#define EDLIN_LINE_MAP_H

#include "../STR/str_fixed.h"
#include "edlin_types.h"

typedef struct {
    str_fixed_t* keys;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_line_map;

#endif 

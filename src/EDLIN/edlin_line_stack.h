#ifndef EDLIN_LINE_STACK_H
#define EDLIN_LINE_STACK_H

#include "edlin_types.h"
#include "../STR/dos_string.h"

typedef struct {
    str_fixed_t** top;
    str_fixed_t** base;
    uint16_t capacity;  
} edlin_line_stack_t;

edlin_line_stack_t* edlin_new_line_stack(void* mem_ptr, edlin_size_t capacity);

void edlin_line_stack_push(edlin_line_stack_t* stack, str_fixed_t* str);

void* edlin_line_stack_pop(edlin_line_stack_t* stack);

#endif

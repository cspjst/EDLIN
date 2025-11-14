#ifndef EDLIN_LINE_STACK_H
#define EDLIN_LINE_STACK_H

#include <stdint.h>

typedef struct {
    void** top;
    void** base;
    uint16_t capacity;  
} edlin_line_stack_t;

 edlin_line_stack_t* edlin_new_line_stack(void* mem_start, uint16_t capacity);

void edlin_line_stack_push(mem_stack_t* stack, void* ptr);

void* edlin_line_stack_pop(mem_stack_t* stack);

#endif

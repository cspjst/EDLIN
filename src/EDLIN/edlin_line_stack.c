#include "edlin_line_stack.h"

edlin_line_stack_t* edlin_new_line_stack(void* mem_ptr, edlin_size_t capacity) {
    edlin_line_stack_t* stack = (edlin_line_stack_t*)mem_ptr;
    stack->base = (str_fixed_t**)((char*)mem_ptr+ sizeof(edlin_line_stack_t));
    stack->top = stack->base;
    stack->capacity = capacity;
    return stack;
}

void edlin_line_stack_push(edlin_line_stack_t* stack, str_fixed_t* str) {
    *(stack->top++) = str;
}

void* edlin_line_stack_pop(edlin_line_stack_t* stack) {
    return *(--stack->top);
}

uint8_t edlin_line_stack_is_empty(edlin_line_stack_t* stack) {
    return stack->top == stack->base;
}

uint8_t edlin_line_stack_is_full(edlin_line_stack_t* stack) {
    return stack->top == stack->base + stack->capacity;
}

edlin_size_t edlin_line_stack_size(edlin_line_stack_t* stack) {
    return stack->top - stack->base;
}

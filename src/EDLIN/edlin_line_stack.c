#include "edlin_line_stack.h"

edlin_line_stack_t* edlin_new_line_stack(void* mem_ptr, edlin_size_t capacity) {
    edlin_line_stack_t* stack = (edlin_line_stack_t*)mem_start;
    stack->base = (void**)((char*)mem_start + sizeof(mem_stack_t));
    stack->top = stack->base;
    stack->capacity = capacity;
    return stack;
}

void edlin_line_stack_push(edlin_line_stack_t* stack, str_fixed_t* str) {
    *(stack->top) = ptr;
    stack->top++;
}

void* edlin_line_stack_pop(edlin_line_stack_t* stack) {
    stack->top--;
    return *(stack->top);
}

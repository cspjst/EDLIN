#ifndef ADT_STACK_IMPL_H
#define ADT_STACK_IMPL_H

#define STACK_IMPLEMENT(T) \
T##_stack_t* T##_stack_new(void* mem, uint16_t cap) { \
    T##_stack_t* stack = (T##_stack_t*)mem; \
    stack->base = (T*)((char*)mem + sizeof(T##_stack_t)); \
    stack->top = stack->base; \
    stack->end = stack->base + cap; \
    return stack; \
} \
void T##_stack_push(T##_stack_t* stack, T value) { \
    *(stack->top) = value; \
    stack->top++; \
} \
T T##_stack_pop(T##_stack_t* stack) { \
    stack->top--; \
    return *(stack->top); \
}

#endif

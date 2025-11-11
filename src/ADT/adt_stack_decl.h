#ifndef ADT_STACK_DECL_H
#define ADT_STACK_DECL_H

/**
 * Generic Abstract Data Type Stack macros that work with any type
 */
#define STACK_DECLARE(T) \
typedef struct { \
    T* top; \
    T* base; \
    T* end; \
} T##_stack_t; \
\
T##_stack_t* T##_stack_new(void* mem, uint16_t cap); \
void T##_stack_push(T##_stack_t* stack, T value); \
T T##_stack_pop(T##_stack_t* stack);

#endif

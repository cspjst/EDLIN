#include "edlin_line_pool.h"
#include <stddef.h>

edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t capacity) {
    // 1. allocate the pool within the arena
    edlin_line_pool_t* pool = (edlin_line_pool_t*)mem_arena_alloc(arena, sizeof(edlin_line_pool_t));
    if(!pool) return NULL;
    // 2. allocate the array of fixed-size strings (the actual line storage)
    pool->lines = (str_fixed_t*)mem_arena_alloc(arena, capacity * sizeof(str_fixed_t));
    if (!pool->lines) return NULL;
    // 3. initialize all lines to empty state (size=0 means line is free/available)
    for (edlin_size_t i = 0; i < capacity; i++) {
        pool->lines[i].size = 0;                // size 0
        pool->lines[i].flags = STR_UNDEFINED;   // Mark line as free
    }
    // 4. set up pool management pointers and counters
    pool->next_free = &pool->lines[0];  // start allocation from first line
    pool->last_line = &pool->lines[capacity - 1];  // ease of bounds checking
    pool->size = 0;                     // no lines allocated yet
    pool->capacity = capacity;         // maximum lines this pool can hold
    return pool;  // ready for line allocation via edlin_alloc_line()
}

str_fixed_t* edlin_alloc_line(edlin_line_pool_t* pool) {
    if (
        !pool                           // null pool error
        || pool->size == pool->capacity // pool full error
    ) return NULL;                      // return fail state
    // 1. allocate a line
    str_fixed_t* new_line = pool->next_free;    // allocate the next free slot
    str_set(new_line, STR_FLAG_VALID);       // bit 0 set = allocated line
    pool->size++;                       // grow the pool
    // 2. find next free line for future allocations - if there is one
    do {
        if (pool->next_free == pool->last_line) {   // searched to the end
            pool->next_free = pool->lines;          // wrap-around to start
        } else {
            pool->next_free++;
        }
        if (pool->next_free->flags == STR_UNDEFINED) return new_line; // found a free line, update next_free and return
    } while (pool->next_free != new_line);          // stop if we searched entire pool
    // 3. no free lines (pool is full after this allocation)
    return new_line;
}

str_fixed_t* edlin_free_line(edlin_line_pool_t* pool, str_fixed_t* line) {
    if(
        !line                           // null line error
        || line < pool->lines           // line ptr out of bounds
        || line > pool->last_line       // line ptr out of bounds
        || line->flags == STR_UNDEFINED // line flag not allocated
    ) return NULL;
    // 1. free the line
    line->size = 0;                     // zero size
    line->flags = STR_UNDEFINED;        // flag as free: clear all flags
    pool->size--;                       // shrink the pool
    pool->next_free = line;             // next free line is now this one
    return line;
}

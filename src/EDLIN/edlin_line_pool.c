#include "edlin_line_pool.h"
#include <stdio.h>

edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t max_lines) {
    // Allocate the pool control structure from the arena
    edlin_line_pool_t* pool = (edlin_line_pool_t*)mem_arena_alloc(arena, sizeof(edlin_line_pool_t));
    if(!pool) return NULL;
    // Allocate the array of fixed-size strings (the actual line storage)
    pool->lines = (str_fixed_t*)mem_arena_alloc(arena, max_lines * sizeof(str_fixed_t));
    if (!pool->lines) return NULL;
    // Initialize all lines to empty state (size=0 means line is free/available)
    for (edlin_size_t i = 0; i < max_lines; i++) {
        pool->lines[i].size = 0;    // size 0
        pool->lines[i].flags = 0;   // Mark line as free
    }
    // Set up pool management pointers and counters
    pool->next_free = &pool->lines[0];   // Start allocation from first line
    pool->last_line = &pool->lines[max_lines - 1];  // For bounds checking
    pool->size = 0;                     // No lines allocated yet
    pool->capacity = max_lines;         // Maximum lines this pool can hold
    return pool;  // Ready for line allocation via edlin_alloc_line()
}

str_fixed_t* edlin_alloc_line(edlin_line_pool_t* pool) {
    if (!pool || pool->size == pool->capacity) return NULL;
    str_fixed_t* new_line = pool->next_free;    // allocate (invariant next_free point to a free line)
    new_line->flags = 1; // bit 0 set = allocated line
    pool->size++;
    // Find next free line for future allocations - if there is one
    do {
        if (pool->next_free == pool->last_line) {
            pool->next_free = pool->lines;      // Move to next line with wrap-around
        } else {
            pool->next_free++;
        }
        if (pool->next_free->flags == 0) return new_line; // found a free line, update next_free and return
    } while (pool->next_free != new_line);  // Stop if we searched entire pool
    return new_line; // If we get here, there are no free lines left (pool is full after this allocation)
}

str_fixed_t* edlin_free_line(edlin_line_pool_t* pool, str_fixed_t* line) {
    if(!line || line < pool->lines || line > pool->last_line || line->flags == 0) return NULL;
    line->size = 0;
    line->flags = 0; // Mark as free: clear all flags
    pool->size--;
    pool->next_free = line;
    return line;
}

#include "edlin_line_pool.h"
#include <stdio.h>

edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t max_lines) {
    edlin_line_pool_t* pool = (edlin_line_pool_t*)mem_arena_alloc(arena, sizeof(edlin_line_pool_t));
    if(!pool) return NULL;
    pool->lines = (str_fixed_t*)mem_arena_alloc(arena, max_lines * sizeof(str_fixed_t));
    if (!pool->lines) return NULL;

    for (edlin_size_t i = 0; i < max_lines; i++) {
        pool->lines[i].size = 0;
        pool->lines[i].flags = 0;
    }

    pool->next_free = &pool->lines[0];   // the next free line is the start of the pool
    pool->last_line = &pool->lines[max_lines - 1];
    pool->size = 0;
    pool->capacity = max_lines;

    return pool;
}

str_fixed_t* edlin_alloc_line(edlin_line_pool_t* pool) {
    if (!pool || pool->size == pool->capacity) return NULL; // Pool full
    str_fixed_t* new_line = pool->next_free;                // the new line

    while(pool->next_free != pool->last_line) {             // search for next free line
        pool->next_free++;
        if(pool->next_free->size == 0) {                  // found the next free line
            pool->size++;                                   // increase the pool size
            return new_line;                                // return the new line
        }
    }                                                       // reached the end no empty lines found
    pool->next_free = pool->lines;                          // so start from the beginning
    while(pool->next_free != new_line) {                    // search for next free line
        pool->next_free++;
        if(pool->next_free->size == 0) {                  // found the next free line
            pool->size++;                                   // increase the pool size
            return new_line;                                // return the new line
        }
    }
    return NULL;                                            // this is bad!
}

str_fixed_t* edlin_free_line(edlin_line_pool_t* pool, str_fixed_t* line) {
    if(!line || line->size == 0) return line;
    line->size = 0;
    pool->size--;
    pool->next_free = line;
    return line;
}

void dump_pool(edlin_line_pool_t* pool) {
    for (edlin_size_t i = 0; i < pool->size; i++) {
        str_out(&pool->lines[i]);
    }
}


/*
// update next search upwards to capacity
while(pool->next->size && pool->next != &pool->lines[pool->capacity - 1]) {
    pool->next++;   // search for the next 0 sized line
    if(pool->next->size == 0) {     // found an empty next slot
        pool->size++;   // increase the pool size
        return line;    // return the new line
    }
}
// no empty slots and reached the end
pool->next = pool->lines;   // so start from the beginning
while(pool->next->size) {
    pool->next++;   // search for the next 0 sized line
    if(pool->next == line) return NULL;     // back to where we started no empty slots found!
}
// found an empty next slot
pool->size++;   // increase the pool size
return line;    // return the new line
 */

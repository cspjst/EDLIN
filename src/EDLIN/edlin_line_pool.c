#include "edlin_line_pool.h"

edlin_line_pool_t* edlin_new_line_pool(mem_arena_t* arena, edlin_size_t lines) {
    edlin_line_pool_t* pool = mem_arena_alloc(arena, sizeof(edlin_line_pool_t));
    if(!pool) return NULL;

    pool->lines = mem_arena_alloc(arena, lines * sizeof(edlin_line_t));
    if (!pool->lines) return NULL;

    for (edlin_size_t i = 0; i < lines; i++) {
        pool->lines[i].size = 0;
    }
    pool->size = 0;
    pool->capacity = lines;
    return pool;
}

edlin_line_t* edlin_first_line(edlin_line_pool_t* pool);

edlin_line_t* edlin_last_line(edlin_line_pool_t* pool);

edlin_line_t* edlin_next_line(edlin_line_pool_t* pool) {
    return &pool->lines[pool->size++];
}

edlin_line_t* edlin_delete_line(edlin_line_pool_t* pool, edlin_line_t* line);

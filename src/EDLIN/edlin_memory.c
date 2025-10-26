#include "edlin_memory.h"
#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../MEM/mem_constants.h"

static mem_arena_t* edlin_arena;

mem_size_bytes_t edlin_new_arena() {
    mem_size_paragraphs_t total_free = mem_get_free_paragraphs();
    edlin_arena = mem_new_arena(total_free);
    return total_free * MEM_PARAGRAPH_SIZE;
}

void edlin_free_arena() {
    mem_free_arena(edlin_arena);
}

void* edlin_arena_alloc(mem_size_bytes_t bytes) {
    return mem_arena_alloc(edlin_arena, bytes);
}

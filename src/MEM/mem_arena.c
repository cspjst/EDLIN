#include "mem_arena.h"
#include "mem_types.h"
#include "mem_constants.h"
#include "../DOS/dos_services.h"
#include <stddef.h>

mem_arena_t* mem_arena_create(mem_size_paragraphs_t paragraphs) {
    mem_address_t addr = {0};
    addr.segoff.segment = dos_allocate_memory_blocks(paragraphs);
    if (!addr.segoff.segment) return NULL;

    mem_arena_t* arena = (mem_arena_t*)addr.ptr;

    arena->segment = addr.segoff.segment;
    arena->base = addr.ptr + sizeof(mem_arena_t);
    arena->free_ptr = arena->base;
    arena->end = arena->base + (paragraphs * MEM_PARAGRAPH_SIZE);

    return arena;
}

void mem_arena_destroy(mem_arena_t* arena) {
    if(arena) dos_free_allocated_memory_blocks(arena->segment);
}

void* mem_arena_alloc(mem_arena_t* arena, mem_size_bytes_t size) {
    char* ptr = arena->free_ptr;
    if(ptr + size <= arena->end) {
        arena->free_ptr += size;
        return ptr;
    }
    return NULL;
}

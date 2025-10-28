#include "mem_arena.h"
#include "mem_types.h"
#include "mem_constants.h"
#include "../DOS/dos_services.h"
#include <stddef.h>

mem_arena_t* mem_new_arena(mem_size_paragraphs_t paragraphs) {
    if(paragraphs * MEM_PARAGRAPH_SIZE < sizeof(mem_arena_t)) return NULL;
    mem_address_t addr = {0};
    addr.segoff.segment = dos_allocate_memory_blocks(paragraphs);
    if(!addr.segoff.segment) return NULL;

    mem_arena_t* arena = (mem_arena_t*)addr.ptr;
    paragraphs--;
    arena->segment = addr.segoff.segment;
    arena->base = addr.ptr + sizeof(mem_arena_t);
    arena->free_ptr = arena->base;
    arena->size = 0;
    arena->capacity = paragraphs * MEM_PARAGRAPH_SIZE;

    return arena;
}

void mem_free_arena(mem_arena_t* arena) {
    if(arena) dos_free_allocated_memory_blocks(arena->segment);
}

char* mem_arena_alloc(mem_arena_t* arena, mem_size_bytes_t size) {
    mem_size_bytes_t remaining = arena->capacity - arena->size;
    if(size <= remaining) {  // ← Check against AVAILABLE space
        char* ptr = arena->free_ptr;
        arena->size += size;
        arena->free_ptr += size;
        return ptr;
    }
    return NULL;
}

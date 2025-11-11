#include "mem_arena.h"
#include "mem_types.h"
#include "mem_constants.h"
#include "../DOS/dos_services.h"
#include <stddef.h>

mem_arena_t* mem_new_dos_arena(mem_size_paragraphs_t paragraphs) {
    if(!paragraphs) return NULL;
    // 1. allocate memory + 16bytes for the mem_arena_t
    mem_address_t addr = {0};
    addr.segoff.segment = dos_allocate_memory_blocks(paragraphs + 1);
    if(!addr.segoff.segment) return NULL;               // DOS allocate failed ?no more memory
    // 2. initialize arena
    mem_arena_t* arena = (mem_arena_t*)addr.ptr;        // allocate the arena within the DOS memory block
    arena->segment = addr.segoff.segment;               // segment home
    arena->base = addr.ptr + sizeof(mem_arena_t);       // start the base above the arena struct
    arena->free_ptr = arena->base;                      // free arena memory starts at the base
    arena->used_size = 0;                               // none used
    arena->free_size = paragraphs * MEM_PARAGRAPH_SIZE; // all free
    arena->capacity = arena->free_size;                 // capacity (bytes)
    return arena;
}

void mem_free_dos_arena(mem_arena_t* arena) {
    if(arena) dos_free_allocated_memory_blocks(arena->segment);
}

char* mem_arena_alloc(mem_arena_t* arena, mem_size_bytes_t size) {
    if(size <= arena->free_size) {      // check against available space
        char* ptr = arena->free_ptr;    // start of the block
        arena->used_size += size;       // increase the used
        arena->free_ptr += size;        // adjust the free ptr
        arena->free_size -= size;       // shrink the remaining
        return ptr;
    }
    return NULL;
}

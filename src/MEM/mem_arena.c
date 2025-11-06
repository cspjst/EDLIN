#include "mem_arena.h"
#include "mem_types.h"
#include "mem_constants.h"
#include "../DOS/dos_services.h"
#include <stddef.h>

mem_arena_t* mem_new_arena(mem_size_paragraphs_t paragraphs) {
    if(
        paragraphs * MEM_PARAGRAPH_SIZE < sizeof(mem_arena_t)   // not even enough room for arena struct
    ) return NULL;
    // 1. allocate memory
    mem_address_t addr = {0};
    addr.segoff.segment = dos_allocate_memory_blocks(paragraphs);
    if(!addr.segoff.segment) return NULL;               // DOS allocate failed ?no more memory
    // 2. initialize arena
    mem_arena_t* arena = (mem_arena_t*)addr.ptr;        // allocate the arena within the DOS memory block
    paragraphs--;                                       // snip off a paragraph for the arena struct
    arena->segment = addr.segoff.segment;               // segment home
    arena->base = addr.ptr + sizeof(mem_arena_t);       // start the base above the arena struct
    arena->free_ptr = arena->base;                      // free arena memory starts at the base
    arena->size = 0;                                    // empty
    arena->capacity = paragraphs * MEM_PARAGRAPH_SIZE;  // capacity (bytes)
    arena->free_size = arena->capacity;
    return arena;
}

void mem_free_arena(mem_arena_t* arena) {
    if(arena) dos_free_allocated_memory_blocks(arena->segment);
}

char* mem_arena_alloc(mem_arena_t* arena, mem_size_bytes_t size) {
    if(size <= arena->free) {      // check against available space
        char* ptr = arena->free_ptr;    // start of the block
        arena->size += size;            // increase the size
        arena->free_ptr += size;        // adjust the free ptr
        arena->free_size -= size;       // shrink the remaining
        return ptr;
    }
    return NULL;
}

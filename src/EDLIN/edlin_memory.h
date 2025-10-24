#ifndef EDLIN_MEMORY_H
#define EDLIN_MEMORY_H

#include "../MEM/mem_types.h"

mem_size_bytes_t edlin_new_arena();

void edlin_free_arena();

void* edlin_arena_allocate();

#endif

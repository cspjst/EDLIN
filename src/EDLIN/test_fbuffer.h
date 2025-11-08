#ifndef TEST_FBUFFER_H
#define TEST_FBUFFER_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "edlin_file_buffer.h"
#include <assert.h>
#include <stdio.h>

void test_file_buffer() {
    printf("Test edlin file buffer\n");
    mem_arena_t* arena = mem_new_arena(4); // 64 bytes
    printf("arena free mem = %li\n", arena->free_size);

}

#endif

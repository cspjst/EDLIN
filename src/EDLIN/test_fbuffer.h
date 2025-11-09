#ifndef TEST_FBUFFER_H
#define TEST_FBUFFER_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "../DOS/dos_services_files.h"
#include "../DOS/dos_tools_files.h"
#include "edlin_file_buffer.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

void test_file_buffer() {
    mem_size_bytes_t sz = 64;
    dos_file_handle_t fh;
    const char* text = "line1\nline2\n";
    uint16_t bytes = 13;
    printf("Test edlin file buffer\n");

    if(!dos_file_exists("TEST.TXT")) {
        dos_create_file("TEST.TXT", CREATE_READ_ONLY, &fh);
        dos_write_file(fh, bytes, text, &bytes);
        dos_close_file(fh);
    }

    mem_arena_t* arena = mem_new_arena(sz / 16); // 64 bytes
    assert(arena->free_size == sz);
    assert(arena->used_size == 0);
    char* mem = (char*)mem_arena_alloc(arena, sz);
    assert(arena->free_size == 0);
    assert(arena->used_size == sz);

    assert(dos_open_file("TEST.TXT", ACCESS_READ_ONLY, &fh) == 0);
    edlin_file_buffer_t* fb = edlin_new_file_buffer(fh, mem, sz);
    assert(fb);
    assert(fb->begin == mem);
    assert(fb->pos == fb->begin);
    assert(fb->end == arena->free_ptr);

    dos_delete_file("TEST.TXT");
    printf("edlin_file_buffer - all tests passed!\n");
}

#endif

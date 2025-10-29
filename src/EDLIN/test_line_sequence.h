#ifndef TEST_LINE_SEQUENCE_H
#define TEST_LINE_SEQUENCE_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "edlin_line_sequence.h"
#include "edlin_types.h"
#include <assert.h>

void dump_sequence(edlin_line_sequence_t* seq) {
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        str_out(as_ptr(seq->line_ptrs[i]), CRLF);
    }
}

void test_line_sequence() {
    mem_size_bytes_t start = mem_get_free_bytes();
    mem_arena_t* arena = mem_new_arena(1024); // 16KB arena
    assert(arena != NULL);

    // Test 0: Confirm data structure integrity
    edlin_size_t sz = 16;
    edlin_line_sequence_t* seq = edlin_new_line_sequence(arena, sz);
    assert(seq != NULL);
    assert(seq->size == 0);
    assert(seq->capacity = sz);
    assert(seq->line_ptrs = &seq->line_ptrs[0]);
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        assert(seq->line_ptrs[i] == 0);
    }

    // Test 1: Simple get
    str_fixed_t* p = 0;
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        seq->line_ptrs[i] = p++;
    }
    p = 0;
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        assert(seq->line_ptrs[i] == p++);
    }

    mem_free_arena(arena);
    assert(start == mem_get_free_bytes());
    str_out(cstr("edlin_line_sequence - all tests passed!"), CRLF);

    dump_sequence(seq);
}

#endif

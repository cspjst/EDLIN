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
    str_out(CRLF);
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
    assert(seq->capacity == sz);
    assert(seq->line_ptrs == &seq->line_ptrs[0]);
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        assert(seq->line_ptrs[i] == 0);
    }

    // Test operations on empty sequence
    assert(edlin_sequence_delete(seq, 0) == NULL); // Delete from empty

    // Test 1: append
    str_fixed_t* p = 0;
    p++;
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        edlin_sequence_append(seq, p++);
    }
    assert(seq->size == seq->capacity);
    assert(seq->size == 16);

    //Test 2: at
    p = 0;
    p++;
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
       assert(edlin_sequence_at(seq, i) == p++);
    }
    assert(edlin_sequence_at(seq, seq->size) == NULL);     // One past end
    assert(edlin_sequence_at(seq, seq->capacity) == NULL); // Way out of bounds
    assert(edlin_sequence_at(seq, (edlin_size_t)-1) == NULL); // Underflow

    // Add after your existing tests:

    // Test 3: Basic delete from middle
    edlin_line_sequence_t* seq2 = edlin_new_line_sequence(arena, 5);
    str_fixed_t* lines[5] = {(str_fixed_t*)1, (str_fixed_t*)2, (str_fixed_t*)3,
                             (str_fixed_t*)4, (str_fixed_t*)5};

    // Fill sequence
    for(int i = 0; i < 5; i++) {
        edlin_sequence_append(seq2, lines[i]);
    }

    // Delete middle element (index 2 = line3)
    str_fixed_t* deleted = edlin_sequence_delete(seq2, 2);
    assert(deleted == lines[2]);
    assert(seq2->size == 4);

    // Verify ripple effect
    assert(edlin_sequence_at(seq2, 0) == lines[0]); // Unchanged
    assert(edlin_sequence_at(seq2, 1) == lines[1]); // Unchanged
    assert(edlin_sequence_at(seq2, 2) == lines[3]); // lines[3] moved to index 2
    assert(edlin_sequence_at(seq2, 3) == lines[4]); // lines[4] moved to index 3

    // Test 4: Delete first element
    deleted = edlin_sequence_delete(seq2, 0);
    assert(deleted == lines[0]);
    assert(seq2->size == 3);
    assert(edlin_sequence_at(seq2, 0) == lines[1]); // Everything shifted down
    assert(edlin_sequence_at(seq2, 1) == lines[3]);
    assert(edlin_sequence_at(seq2, 2) == lines[4]);

    // Test 5: Delete last element
    deleted = edlin_sequence_delete(seq2, 2); // Now last element
    assert(deleted == lines[4]);
    assert(seq2->size == 2);
    assert(edlin_sequence_at(seq2, 0) == lines[1]);
    assert(edlin_sequence_at(seq2, 1) == lines[3]);

    // Test 6: Delete until empty
    edlin_sequence_delete(seq2, 0);
    edlin_sequence_delete(seq2, 0);
    assert(seq2->size == 0);
    assert(edlin_sequence_delete(seq2, 0) == NULL); // Delete from empty

    // Test 7: Delete with out-of-bounds indices
    assert(edlin_sequence_delete(seq2, 5) == NULL); // Index > size
    assert(edlin_sequence_delete(seq2, (edlin_size_t)-1) == NULL); // Underflow

    // Test 8: Verify array state after deletions
    for(edlin_size_t i = seq2->size; i < seq2->capacity; i++) {
        assert(seq2->line_ptrs[i] == NULL); // Trailing elements should be nullified
    }

    // Test 9: Interleaved append/delete
    edlin_line_sequence_t* seq3 = edlin_new_line_sequence(arena, 3);
    edlin_sequence_append(seq3, (str_fixed_t*)100);
    edlin_sequence_append(seq3, (str_fixed_t*)200);
    edlin_sequence_delete(seq3, 0); // Delete first
    edlin_sequence_append(seq3, (str_fixed_t*)300); // Should append to end

    assert(seq3->size == 2);
    assert(edlin_sequence_at(seq3, 0) == (str_fixed_t*)200); // Remaining element
    assert(edlin_sequence_at(seq3, 1) == (str_fixed_t*)300); // New append

    // Test 10: all the NULLs
    assert(edlin_sequence_at(NULL, 0) == NULL);
    assert(edlin_sequence_append(NULL, (str_fixed_t*)1) == NULL);
    assert(edlin_sequence_delete(NULL, 0) == NULL);
    assert(edlin_sequence_append(seq, NULL) == NULL);
    assert(edlin_sequence_insert(seq, 0, NULL) == NULL);

    edlin_line_sequence_t* s = edlin_new_line_sequence(arena, 5);

    // Setup: [A, B, C]
    str_fixed_t* A = (str_fixed_t*)1;
    str_fixed_t* B = (str_fixed_t*)2;
    str_fixed_t* C = (str_fixed_t*)3;
    str_fixed_t* X = (str_fixed_t*)99;

    edlin_sequence_append(s, A);
    edlin_sequence_append(s, B);
    edlin_sequence_append(s, C);

    // Test 1: Insert at beginning
    assert(edlin_sequence_insert(s, 0, X) == X);
    assert(s->size == 4);
    assert(edlin_sequence_at(s, 0) == X);  // [X, A, B, C]
    assert(edlin_sequence_at(s, 1) == A);
    assert(edlin_sequence_at(s, 2) == B);
    assert(edlin_sequence_at(s, 3) == C);

    // Test 2: Insert at middle
    str_fixed_t* Y = (str_fixed_t*)98;
    assert(edlin_sequence_insert(s, 2, Y) == Y);
    assert(s->size == 5);
    assert(edlin_sequence_at(s, 0) == X);  // [X, A, Y, B, C]
    assert(edlin_sequence_at(s, 1) == A);
    assert(edlin_sequence_at(s, 2) == Y);
    assert(edlin_sequence_at(s, 3) == B);
    assert(edlin_sequence_at(s, 4) == C);

    // Test 3: Insert at end (should work like append)
    str_fixed_t* Z = (str_fixed_t*)97;
    assert(edlin_sequence_insert(s, s->size, Z) == NULL); // Full now

    // Test 4: Error conditions
    assert(edlin_sequence_insert(NULL, 0, Z) == NULL);
    assert(edlin_sequence_insert(s, 0, NULL) == NULL);
    assert(edlin_sequence_insert(s, 6, Z) == NULL);  // index > size
    assert(edlin_sequence_insert(s, (edlin_size_t)-1, Z) == NULL); // underflow

    // Test 5: Insert into empty sequence
    edlin_line_sequence_t* empty_seq = edlin_new_line_sequence(arena, 3);
    assert(edlin_sequence_insert(empty_seq, 0, A) == A);
    assert(empty_seq->size == 1);
    assert(edlin_sequence_at(empty_seq, 0) == A);

    // Test 6: Insert at exact size position (legal - makes it like append)
    assert(edlin_sequence_insert(empty_seq, 1, B) == B);
    assert(empty_seq->size == 2);
    assert(edlin_sequence_at(empty_seq, 0) == A);
    assert(edlin_sequence_at(empty_seq, 1) == B);

    str_out(as_dec(mem_get_free_bytes()), CRLF);
    mem_free_arena(arena);
    assert(start == mem_get_free_bytes());
    str_out(as_dec(start), CRLF);
    str_out(cstr("edlin_line_sequence - all tests passed!"), CRLF);
}

#endif

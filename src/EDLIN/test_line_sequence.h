#ifndef TEST_LINE_SEQUENCE_H
#define TEST_LINE_SEQUENCE_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "edlin_line_sequence.h"
#include "edlin_types.h"
#include <assert.h>

void test_line_sequence() {
    mem_size_bytes_t start = mem_get_free_bytes();
    mem_arena_t* arena = mem_new_arena(1024); // 16KB arena
    assert(arena != NULL);

    str_fixed_t lines[5] = {
        {"A,", 2, 1},
        {"B,", 2, 1},
        {"C,", 2, 1},
        {"D,", 2, 1},
        {"E,", 2, 1},
    };

    str_fixed_t more_lines[2] = {
        {"V,", 2, 1},
        {"W,", 2, 1},
        //{"X,", 2, 1},
        //{"Y,", 2, 1},
        //{"Z,", 2, 1},
    };

    //str_out(cstr("Test 0: Confirm data structure integrity"), CRLF);
    edlin_size_t sz = 5;
    edlin_line_sequence_t* seq = edlin_new_line_sequence(arena, sz);
    assert(seq != NULL);
    assert(seq->size == 0);
    assert(seq->capacity == sz);
    assert(seq->line_ptrs == &seq->line_ptrs[0]);
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
        assert(seq->line_ptrs[i] == 0);
    }
    //edlin_sequence_dump(seq);

    //str_out(cstr("Test operations on empty sequence"), CRLF);
    assert(edlin_sequence_remove(seq, 0) == NULL); // Delete from empty

    //str_out(cstr("Test 1: append"), CRLF);
    //str_out(cstr("Fill sequence"), CRLF);
    for(int i = 0; i < 5; i++) {
        assert(edlin_sequence_append(seq, &lines[i]));
    }
    assert(seq->size == seq->capacity);
    assert(seq->size == 5);
    //edlin_sequence_dump(seq);

    //str_out(cstr("Test 2: at"), CRLF);
    for(edlin_size_t i = 0; i <seq->capacity; ++i) {
       assert(edlin_sequence_at(seq, i) == &lines[i]);
       assert(edlin_sequence_at(seq, i)->size == 2);
    }
    assert(edlin_sequence_at(seq, seq->size) == NULL);     // One past end
    assert(edlin_sequence_at(seq, seq->capacity) == NULL); // Way out of bounds
    assert(edlin_sequence_at(seq, (edlin_size_t)-1) == NULL); // Underflow
    //edlin_sequence_dump(seq);
    assert(seq->size == 5);

    assert(edlin_sequence_remove(seq, 1) == &lines[1]);
    assert(!str_test(&lines[1], STR_FLAG_ALLOCATED));
    //edlin_sequence_dump(seq);

    edlin_sequence_remove_all(seq);
    assert(seq->size == 0);

    //str_out(cstr("Empty: "));
    //edlin_sequence_dump(seq);

    //str_out(cstr("Test 3: Basic delete from middle"), CRLF);
    edlin_line_sequence_t* seq2 = edlin_new_line_sequence(arena, 5);
    //str_out(cstr("Fill sequence"), CRLF);
    for(int i = 0; i < 5; i++) {
        assert(!str_test(&lines[i], STR_FLAG_ALLOCATED));
        assert(edlin_sequence_append(seq2, &lines[i]));
    }
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Delete middle element (index 2 = line3)"), CRLF);
    str_fixed_t* deleted = edlin_sequence_remove(seq2, 2);
    assert(deleted == &lines[2]);
    assert(seq2->size == 4);
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Verify ripple effect"), CRLF);
    assert(edlin_sequence_at(seq2, 0) == &lines[0]); // Unchanged
    assert(edlin_sequence_at(seq2, 1) == &lines[1]); // Unchanged
    assert(edlin_sequence_at(seq2, 2) == &lines[3]); // lines[3] moved to index 2
    assert(edlin_sequence_at(seq2, 3) == &lines[4]); // lines[4] moved to index 3
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Test 4: Delete first element"), CRLF);
    deleted = edlin_sequence_remove(seq2, 0);
    assert(deleted == &lines[0]);
    assert(seq2->size == 3);
    assert(edlin_sequence_at(seq2, 0) == &lines[1]); // Everything shifted down
    assert(edlin_sequence_at(seq2, 1) == &lines[3]);
    assert(edlin_sequence_at(seq2, 2) == &lines[4]);
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Test 5: Delete last element"), CRLF);
    deleted = edlin_sequence_remove(seq2, 2); // Now last element
    assert(deleted == &lines[4]);
    assert(seq2->size == 2);
    assert(edlin_sequence_at(seq2, 0) == &lines[1]);
    assert(edlin_sequence_at(seq2, 1) == &lines[3]);
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Test 6: Delete until empty"), CRLF);
    edlin_sequence_remove(seq2, 0);
    edlin_sequence_remove(seq2, 0);
    assert(seq2->size == 0);
    assert(edlin_sequence_remove(seq2, 0) == NULL); // Delete from empty
    //edlin_sequence_dump(seq2);

    //str_out(cstr("Test 7: Delete with out-of-bounds indices"), CRLF);
    assert(edlin_sequence_remove(seq2, 5) == NULL); // Index > size
    assert(edlin_sequence_remove(seq2, (edlin_size_t)-1) == NULL); // Underflow

    //str_out(cstr("Test 8: Verify array state after deletions"), CRLF);
    for(edlin_size_t i = seq2->size; i < seq2->capacity; i++) {
        assert(seq2->line_ptrs[i] == NULL); // Trailing elements should be nullified
    }

    //str_out(cstr("Test 9: Interleaved append/delete"), CRLF);
    edlin_line_sequence_t* seq3 = edlin_new_line_sequence(arena, 3);
    edlin_sequence_append(seq3, &lines[0]);
    edlin_sequence_append(seq3, &lines[2]);
    edlin_sequence_remove(seq3, 0); // Delete first
    edlin_sequence_append(seq3, &lines[1]); // Should append to end
    //edlin_sequence_dump(seq3);

    assert(seq3->size == 2);
    assert(edlin_sequence_at(seq3, 0) == &lines[2]); // Remaining element
    assert(edlin_sequence_at(seq3, 1) == &lines[1]); // New append

    //str_out(cstr("Test 10: all the NULLs"), CRLF);
    assert(edlin_sequence_at(NULL, 0) == NULL);
    assert(edlin_sequence_append(NULL, (str_fixed_t*)1) == NULL);
    assert(edlin_sequence_remove(NULL, 0) == NULL);
    assert(edlin_sequence_append(seq, NULL) == NULL);
    assert(edlin_sequence_insert(seq, 0, NULL) == NULL);

    edlin_sequence_remove_all(seq3);

    edlin_line_sequence_t* s = edlin_new_line_sequence(arena, 5);

    //str_out(cstr("Setup: [A, B, C]"), CRLF);
    for(int i = 0; i < 3; i++) {
        assert(edlin_sequence_append(s, &lines[i]));
    }
    //edlin_sequence_dump(s);

    //str_out(cstr("Test 1: Insert at beginning"), CRLF);
    assert(edlin_sequence_insert(s, 0, &more_lines[0]) == &more_lines[0]);
    //edlin_sequence_dump(s);
    assert(s->size == 4);
    assert(edlin_sequence_at(s, 0) == &more_lines[0]);  // [U, A, B, C]
    assert(edlin_sequence_at(s, 1) == &lines[0]);
    assert(edlin_sequence_at(s, 2) == &lines[1]);
    assert(edlin_sequence_at(s, 3) == &lines[2]);
    //edlin_sequence_dump(s);

    //str_out(cstr("Test 2: Insert at middle"), CRLF);
    assert(edlin_sequence_insert(s, 2, &more_lines[1]) == &more_lines[1]);
    assert(s->size == 5);
    assert(edlin_sequence_at(s, 0) == &more_lines[0]);  // [X, A, Y, B, C]
    assert(edlin_sequence_at(s, 1) == &lines[0]);
    assert(edlin_sequence_at(s, 2) == &more_lines[1]);
    assert(edlin_sequence_at(s, 3) == &lines[1]);
    assert(edlin_sequence_at(s, 4) == &lines[2]);
    //edlin_sequence_dump(s);

    //str_out(cstr("Test 3: Insert at end (should work like append)"), CRLF);
    assert(edlin_sequence_insert(s, s->size, &more_lines[2]) == NULL); // Full now
    //edlin_sequence_dump(s);

    //str_out(cstr("Test 4: Error conditions"), CRLF);
    assert(edlin_sequence_insert(NULL, 0, &more_lines[1]) == NULL);
    assert(edlin_sequence_insert(s, 0, NULL) == NULL);
    assert(edlin_sequence_insert(s, 6, &more_lines[1]) == NULL);  // index > size
    assert(edlin_sequence_insert(s, (edlin_size_t)-1, &more_lines[1]) == NULL); // underflow
    //edlin_sequence_dump(s);
    edlin_sequence_remove_all(s);

    //str_out(cstr("Test 5: Insert into empty sequence"), CRLF);
    edlin_line_sequence_t* empty_seq = edlin_new_line_sequence(arena, 3);
    assert(edlin_sequence_insert(empty_seq, 0, &more_lines[0]) == &more_lines[0]);
    assert(empty_seq->size == 1);
    assert(edlin_sequence_at(empty_seq, 0) == &more_lines[0]);
    //edlin_sequence_dump(s);

    //str_out(cstr("Test 6: Insert at exact size position (legal - makes it like append)"), CRLF);
    assert(edlin_sequence_insert(empty_seq, 1, &more_lines[1]) == &more_lines[1]);
    assert(empty_seq->size == 2);
    assert(edlin_sequence_at(empty_seq, 0) == &more_lines[0]);
    assert(edlin_sequence_at(empty_seq, 1) == &more_lines[1]);
    //edlin_sequence_dump(s);

    //str_out(as_dec(mem_get_free_bytes()), CRLF);
    mem_free_arena(arena);
    assert(start == mem_get_free_bytes());
    //str_out(as_dec(start), CRLF);
    str_out(cstr("edlin_line_sequence - all tests passed!"), CRLF);
}

#endif

#ifndef TEST_LINE_POOL
#define TEST_LINE_POOL

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "edlin_line_pool.h"
#include <assert.h>

void test_line_pool() {
    mem_size_bytes_t start = mem_get_free_bytes();
    mem_arena_t* arena = mem_new_arena(1024); // 16KB arena
    assert(arena != NULL);
    edlin_line_pool_t* pool = edlin_new_line_pool(arena, 5); // 5-line pool
    assert(pool != NULL);
    assert(pool->size == 0);
    assert(pool->capacity == 5);
    assert(pool->lines = &pool->lines[0]);
    assert(pool->next_free == &pool->lines[0]);
    assert(pool->last_line == &pool->lines[4]);

    // Test 1: Allocate first line
    str_fixed_t* line1 = edlin_alloc_line(pool);
    assert(line1 != NULL);
    assert(pool->size == 1);
    //str_cstr(line1, " First line");
    //str_out(as_ptr(line1), line1, CRLF);

    // Test 2: Allocate second line
    str_fixed_t* line2 = edlin_alloc_line(pool);
    assert(line2 != NULL);
    assert(pool->size == 2);
    //str_cstr(line2, " Second line");
    //str_out(as_ptr(line2), line2, CRLF);

    // Test 3: Free first line
    edlin_free_line(pool, line1);
    assert(pool->size == 1);
    assert(line1->size == 0);

    // Test 4: Reallocate freed line
    str_fixed_t* line3 = edlin_alloc_line(pool);
    assert(line3 == line1); // Should reuse freed slot
    assert(pool->size == 2);
    //str_cstr(line3, " Reused line");
    //str_out(as_ptr(line3), line3, CRLF);

    // Test 5: Fill pool to capacity
    str_fixed_t* line4 = edlin_alloc_line(pool);
    assert(pool->size == 3);
    //str_out(as_ptr(line4), line4, CRLF);
    str_fixed_t* line5 = edlin_alloc_line(pool);
    assert(pool->size == 4);
    //str_out(as_ptr(line5), line5, CRLF);
    str_fixed_t* line6 = edlin_alloc_line(pool);
    assert(pool->size == 5);
    //str_cstr(line6, " Last line");
    //str_out(as_ptr(line6), line6, CRLF);

    // Test 6: Pool should be full
    str_fixed_t* line7 = edlin_alloc_line(pool);
    assert(line7 == NULL);
    assert(pool->size == 5);  // Size unchanged when allocation fails
    //str_out(as_ptr(pool->last_line), pool->last_line, CRLF);

    //Test 7: Free NULL/invalid line
    edlin_free_line(pool, NULL);                    // Free NULL pointer
    assert(pool->size == 5);                        // Size unchanged

    str_fixed_t foreign_line = {"",1,0};                       // Line not from this pool
    edlin_free_line(pool, &foreign_line);
    assert(pool->size == 5);                        // Size unchanged

    // Test 8: Multiple frees then allocations
    assert(edlin_free_line(pool, line3));                   // Free line3
    assert(line4 != NULL);
    assert(line4->flags == 1);  // Should be occupied
    assert(line4 >= pool->lines && line4 <= pool->last_line);  // Should be in bounds
    assert(edlin_free_line(pool, line4));                   // Free line4
    assert(pool->size == 3);                        // Now 3 lines in use

    str_fixed_t* line8 = edlin_alloc_line(pool);    // Should reuse a freed slot
    str_fixed_t* line9 = edlin_alloc_line(pool);    // Should reuse another freed slot
    assert(pool->size == 5);                        // Back to full
    assert(line8 != NULL);
    assert(line9 != NULL);

    // Test 9: Verify next_free invariant after operations
    assert(pool->next_free->size == 0);             // next_free must point to free line

    // Test 10: Free then immediate realloc same line
    edlin_free_line(pool, line5);                   // Free line5
    assert(pool->size == 4);
    str_fixed_t* line10 = edlin_alloc_line(pool);   // Should reuse line5 immediately
    assert(line10 == line5);
    assert(pool->size == 5);

    // Test 11: Force wrap-around allocation
    // Fill pool, free first line, then allocate until we wrap
    edlin_free_line(pool, line8);                   // Free a line
    assert(pool->size == 4);

    // Allocate multiple times to force next_free to wrap around
    str_fixed_t* line11 = edlin_alloc_line(pool);
    str_fixed_t* line12 = edlin_alloc_line(pool);   // This should cause wrap-around
    assert(pool->size == 5);
    assert(pool->next_free->flags == 1);             // Invariant broken in this one case but...

    // Test 12: Pool still full after all operations
    str_fixed_t* line13 = edlin_alloc_line(pool);
    assert(line13 == NULL);                         // Still full
    assert(pool->size == 5);                        // Size unchanged

    // Test 13: Single-line pool (minimum capacity)
    edlin_line_pool_t* tiny_pool = edlin_new_line_pool(arena, 1);
    assert(tiny_pool != NULL);
    str_fixed_t* lone_line = edlin_alloc_line(tiny_pool);
    assert(lone_line != NULL);
    assert(lone_line == tiny_pool->lines);          // Only one line available
    assert(edlin_alloc_line(tiny_pool) == NULL);    // Should be full
    edlin_free_line(tiny_pool, lone_line);          // Free the line
    assert(edlin_alloc_line(tiny_pool) == lone_line); // Should reuse the only line

    // Test 14: Consecutive allocs without any free (sequential allocation)
    edlin_line_pool_t* seq_pool = edlin_new_line_pool(arena, 4);
    str_fixed_t* seq_lines[4];
    for (int i = 0; i < 4; i++) {
        seq_lines[i] = edlin_alloc_line(seq_pool);
        assert(seq_lines[i] != NULL);
        assert(seq_lines[i] == &seq_pool->lines[i]); // Should allocate sequentially
    }
    assert(edlin_alloc_line(seq_pool) == NULL);     // Should be full

    // Test 15: Alloc after freeing ALL lines (complete pool reset)
    for (int i = 0; i < 4; i++) {
        assert(edlin_free_line(seq_pool, seq_lines[i])); // Free all lines
    }
    assert(seq_pool->size == 0);                    // Pool should be empty
    // Now allocate all lines again
    for (int i = 0; i < 4; i++) {
        assert(edlin_alloc_line(seq_pool) != NULL); // Should all succeed
    }
    assert(seq_pool->size == 4);                    // Should be full again

    // Test 16: Stress test - alloc/free pattern that fragments the pool
    edlin_line_pool_t* frag_pool = edlin_new_line_pool(arena, 6);
    // Allocate all lines
    str_fixed_t* frag_lines[6];
    for (int i = 0; i < 6; i++) {
        frag_lines[i] = edlin_alloc_line(frag_pool);
    }
    // Free every other line to create fragmentation
    assert(edlin_free_line(frag_pool, frag_lines[1]));
    assert(edlin_free_line(frag_pool, frag_lines[3]));
    assert(edlin_free_line(frag_pool, frag_lines[5]));
    assert(frag_pool->size == 3);                   // 3 occupied, 3 free
    // Now allocate - should find the free slots despite fragmentation
    assert(edlin_alloc_line(frag_pool) != NULL);
    assert(edlin_alloc_line(frag_pool) != NULL);
    assert(edlin_alloc_line(frag_pool) != NULL);
    assert(frag_pool->size == 6);                   // Should be full again

    // Test 17: Edge - alloc when next_free points exactly to last_line
    edlin_line_pool_t* edge_pool = edlin_new_line_pool(arena, 3);
    // Manually set next_free to last_line (simulate wrap-around state)
    edge_pool->next_free = edge_pool->last_line;
    // This allocation should wrap around to beginning
    str_fixed_t* wrap_line = edlin_alloc_line(edge_pool);
    assert(wrap_line == edge_pool->last_line);      // Should use last_line
    assert(edge_pool->next_free == edge_pool->lines); // Should wrap to start

    // Test 18: Double-free protection
    edlin_free_line(pool, line8);                   // Free a line
    str_fixed_t* double_line = edlin_alloc_line(pool);
    assert(double_line);
    assert(edlin_free_line(pool, double_line));
    assert(!edlin_free_line(pool, double_line));  // Should handle gracefully
    //str_out(as_dec(pool->size), CRLF);
    assert(pool->size == 4);

    // Test 19: Free then immediate realloc data integrity
    str_fixed_t* data_line = edlin_alloc_line(pool);
    str_str(data_line, cstr("Test data"));
    assert(data_line->size == 9);
    assert(data_line->flags == 1);
    edlin_free_line(pool, data_line);
    assert(data_line->size == 0);  // Should be reset
    assert(data_line->flags == 0);
    str_fixed_t* same_line = edlin_alloc_line(pool);
    // The line should be reset (size=0) but same memory location
    assert(same_line == data_line);
    assert(same_line->size == 0);  // Should be reset
    assert(same_line->flags == 1);

    mem_free_arena(arena);
    assert(start == mem_get_free_bytes());
    str_out(cstr("edlin_line_pool - all tests passed!"), CRLF);
}

#endif

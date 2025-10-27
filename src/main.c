#include "MEM/mem_arena.h"
#include "MEM/mem_constants.h"
#include "MEM/mem_types.h"
#include "STR/dos_string.h"
#include "MEM/mem_tools.h"
#include "EDLIN/edlin_line_pool.h"
#include <assert.h>

int main() {
    mem_arena_t* arena = mem_new_arena(1024); // 16KB arena
    assert(arena != NULL);
    edlin_line_pool_t* pool = edlin_new_line_pool(arena, 5); // 5-line pool
    assert(pool != NULL);
    assert(pool->size == 0);
    assert(pool->capacity = 5);
    assert(pool->lines = &pool->lines[0]);
    assert(pool->next_free == &pool->lines[0]);
    assert(pool->last_line == &pool->lines[4]);

    // Test 1: Allocate first line
    str_fixed_t* line1 = edlin_alloc_line(pool);
    assert(line1 != NULL);
    assert(pool->size == 1);
    str_cstr(line1, " First line");
    str_out(as_ptr(line1), line1, CRLF);

    // Test 2: Allocate second line
    str_fixed_t* line2 = edlin_alloc_line(pool);
    assert(line2 != NULL);
    assert(pool->size == 2);
    str_cstr(line2, " Second line");
    str_out(as_ptr(line2), line2, CRLF);

    // Test 3: Free first line
    edlin_free_line(pool, line1);
    assert(pool->size == 1);
    assert(line1->size == 0);

    // Test 4: Reallocate freed line
    str_fixed_t* line3 = edlin_alloc_line(pool);
    assert(line3 == line1); // Should reuse freed slot
    assert(pool->size == 2);
    str_cstr(line3, " Reused line");
    str_out(as_ptr(line3), line3, CRLF);

    // Test 5: Fill pool to capacity
    str_fixed_t* line4 = edlin_alloc_line(pool);
    assert(pool->size == 3);
    str_out(as_ptr(line4), line4, CRLF);
    str_fixed_t* line5 = edlin_alloc_line(pool);
    assert(pool->size == 4);
    str_out(as_ptr(line5), line5, CRLF);
    str_fixed_t* line6 = edlin_alloc_line(pool);
    assert(pool->size == 5);
    str_cstr(line6, " Last line");
    str_out(as_ptr(line6), line6, CRLF);

    // Test 6: Pool should be full
    str_fixed_t* line7 = edlin_alloc_line(pool);
    assert(line7 == NULL);
    assert(pool->size == 5);  // Size unchanged when allocation fails
    str_out(as_ptr(pool->last_line), pool->last_line, CRLF);

    str_out(cstr("All tests passed!"), CRLF);
    str_out(as_dec(mem_get_free_bytes()), CRLF);
    mem_free_arena(arena);
}

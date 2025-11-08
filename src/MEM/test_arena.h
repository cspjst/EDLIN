#ifndef TEST_ARENA_H
#define TEST_ARENA_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "mem_types.h"
#include <assert.h>
#include <string.h>

void test_mem_arena() {
    mem_size_bytes_t start = mem_get_free_bytes();
    str_out(as_dec(start), CRLF);
    // Test 1: Basic creation
    mem_arena_t* arena = mem_new_arena(10); // 10 paragraphs = 160 bytes
    assert(arena != NULL);
    assert(arena->used_size == 0);
    assert(arena->capacity == 10 * MEM_PARAGRAPH_SIZE);
    assert(arena->free_size == 10 * MEM_PARAGRAPH_SIZE);

    // Test 2: Simple allocation
    char* ptr1 = mem_arena_alloc(arena, 32);
    assert(ptr1 != NULL);
    assert(ptr1 == arena->base);
    assert(arena->used_size == 32);
    assert(arena->free_ptr == arena->base + 32);
    assert(arena->free_size == arena->capacity - 32);

    // Test 3: Sequential allocations
    char* ptr2 = mem_arena_alloc(arena, 64);
    assert(ptr2 != NULL);
    assert(ptr2 == arena->base + 32);
    assert(arena->used_size == 96);
    assert(arena->free_ptr == arena->base + 96);

    // Test 4: Fill to capacity
    char* ptr3 = mem_arena_alloc(arena, 64); // 96 + 64 = 160 (exact capacity)
    assert(ptr3 != NULL);
    assert(arena->used_size == 160);
    assert(arena->free_ptr == arena->base + 160);
    assert(arena->free_size == 0);

    // Test 5: Over-allocation should fail
    char* ptr4 = mem_arena_alloc(arena, 1);
    assert(ptr4 == NULL);
    assert(arena->used_size == 160); // Size unchanged

    // Test 6: Data integrity
    strcpy(ptr1, "Hello");
    strcpy(ptr2, "World");
    assert(strcmp(ptr1, "Hello") == 0);
    assert(strcmp(ptr2, "World") == 0);

    // Test 7: Cleanup
    mem_free_arena(arena);

    // Test 8: Insufficient memory on creation
    mem_arena_t* small_arena = mem_new_arena(0);
    assert(small_arena == NULL);

    mem_free_arena(arena);
    assert(start == mem_get_free_bytes());
    str_out(as_dec(mem_get_free_bytes()), CRLF);
    str_out(cstr("mem_arena - all tests passed!"), CRLF);
}

#endif

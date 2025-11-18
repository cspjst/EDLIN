#ifndef TEST_STDIO_H
#define TEST_STDIO_H

#include "tiny_stdio.h"
#include "tiny_errno.h"

//#include <assert.h>
//#include <string.h>
//#include <stdarg.h>

void test_stdio_basic() {

    fputc('A', stdout);

    /*
    printf("Testing stdio basic functions...\n");

    // Test 1: Basic putchar output
    printf("1. Testing putchar...\n");
    int result = putchar('A');
    putchar('B');
    putchar('\n');
    printf("putchar returned: %d (expected: %d)\n", result, 'A');
    assert(result == 'A');
    putchar('\n');

    // Test 2: Multiple characters
    printf("2. Testing multiple putchars...\n");
    putchar('H'); putchar('e'); putchar('l'); putchar('l'); putchar('o');
    putchar('\n');

    printf("Basic stdio tests passed!\n");
    */
}

// Helper to capture output (simplified - would need real capture in DOS)
/*
static int test_printf(const char* format, ...) {
    // In real test, you'd capture output to buffer
    // For now, just verify it doesn't crash and returns 0
    va_list args;
    va_start(args, format);
    int result = printf(format, args);
    va_end(args);
    return result;
}

void test_printf_basic() {
    printf("Testing printf basic formats...\n");

    // Test 1: Basic strings and chars
    printf("1. Basic strings: %s\n", "Hello");
    printf("2. Chars: %c%c%c\n", 'A', 'B', 'C');
    printf("3. Mixed: %s %c %s\n", "Letter", 'X', "test");

    // Test 2: Integers
    printf("4. Decimal: %d\n", 42);
    printf("5. Negative: %d\n", -123);
    printf("6. Zero: %d\n", 0);
    printf("7. Large: %d\n", 32767);
    printf("8. Large negative: %d\n", -32768);

    // Test 3: Unsigned
    printf("9. Unsigned: %u\n", 65535);
    printf("10. Unsigned zero: %u\n", 0);

    // Test 4: Hex
    printf("11. Hex lower: %x\n", 0xDEAD);
    printf("12. Hex upper: %X\n", 0xBEEF);
    printf("13. Hex zero: %x\n", 0);

    // Test 5: Octal
    printf("14. Octal: %o\n", 511); // 777 in octal
    printf("15. Octal zero: %o\n", 0);
}

void test_printf_edge_cases() {
    printf("Testing printf edge cases...\n");

    // Test 1: Format specifier edge cases
    printf("1. Empty string: '%s'\n", "");
    printf("2. Null string: '%s'\n", NULL);
    printf("3. Percent literal: 100%% complete\n");
    printf("4. Multiple percents: %% %% %%\n");

    // Test 2: Number edge cases
    printf("5. Max int: %d\n", 2147483647);
    printf("6. Max unsigned: %u\n", 4294967295U);
    printf("7. Single digit: %d\n", 7);

    // Test 3: Long modifiers (should work due to our simplification)
    printf("8. Long decimal: %ld\n", 123456789L);
    printf("9. Long unsigned: %lu\n", 4000000000UL);

    // Test 4: Boundary values
    printf("10. Hex boundary: %x\n", 0xFFFFFFFF);
    printf("11. Octal boundary: %o\n", 077777777);

    // Test 5: Special characters in strings
    printf("12. Special chars: %s\n", "Tab\tNewline\nCR\r");
    printf("13. Format chars: %s\n", "Percent% Slash\\ Quote\"");
}

void test_printf_recursive() {
    printf("Testing recursive number formatting...\n");

    // Test recursive depth with various numbers
    printf("1. Single digit: %d\n", 1);
    printf("2. Two digits: %d\n", 12);
    printf("3. Three digits: %d\n", 123);
    printf("4. Four digits: %d\n", 1234);
    printf("5. Many digits: %d\n", 1234567890);

    // Test base conversions
    printf("6. Binary pattern: %x\n", 0xAAAAAAAA);
    printf("7. Alternating bits: %o\n", 01234567);

    // Test recursive with different bases
    printf("8. Hex recursive: %x\n", 0x12345678);
    printf("9. Octal recursive: %o\n", 01234567);
    printf("10. Large unsigned: %u\n", 3000000000U);
}

void test_printf_error_conditions() {
    printf("Testing printf error conditions...\n");

    // Test 1: Unknown format specifiers
    printf("1. Unknown specifier: %q (should show %q)\n");
    printf("2. Incomplete format: % (should show % )\n");
    printf("3. Double percent: %%d should show %d literally\n");

    // Test 2: Empty format string
    printf("4. Empty format:\n", 42); // Extra arg should be ignored
    printf("5. Just text, no formats\n");

    // Test 3: Missing arguments (will read garbage - but shouldn't crash)
    printf("6. Missing string: %s\n"); // Will show garbage but not crash
    printf("7. Missing number: %d\n"); // Will show garbage but not crash
}
*/
void test_stdio() {
    printf(" Testing Tiny stdio.h \n");

    test_stdio_basic();
    //test_printf_basic();
    //test_printf_edge_cases();
    //test_printf_recursive();
    //test_printf_error_conditions();

    printf("=== All printf tests completed (visual inspection required) ===\n");
}

#endif

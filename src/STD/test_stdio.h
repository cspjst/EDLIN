#ifndef TEST_STDIO_H
#define TEST_STDIO_H

#include "tiny_stdio.h"
#include "tiny_errno.h"
#include "tiny_stdlib.h"
#include "tiny_assert.h"

void test_stdio_basic() {

    fputc(fputc('a', stdout) + 2, stdout);
    assert(putc('b', stdout) == 'b');
    fputc('e', stderr);
    putc('E', stderr);

    // Test basic character output
    putchar('A');
    putchar('B');
    putchar('C');
    putchar('\n');

    // Test numeric values
    for (int i = 0; i < 10; i++) {
        putchar('0' + i);
    }
    putchar('\n');

    // Test special characters
    putchar('\t');
    putchar('X');
    putchar('\n');

    // Test basic string output
    puts("Hello, DOS!");
    puts("");
    puts("This\nis\na\ntest\tstring");
    puts("Test 123");
    puts("Special chars: !@#$%^&*()");
    puts(NULL);
}
void test_printf_integers(void) {
    printf("Testing printf integers...\n");

    // Test basic signed integers
    printf("Signed: %d %d %d\n", 0, 42, -17);

    // Test unsigned integers
    printf("Unsigned: %u %u\n", 4294967254U, 12345U);

    // Test long integers
    printf("Long: %ld %ld\n", 123456L, -987654L);

    // Test zero and boundary values
    printf("Zero: %d %u\n", 0, 0U);
    printf("Max int: %d\n", 32767);  // Assuming 16-bit int
    printf("Min int: %d\n", -32768);

    printf("Integer test complete\n");
}

void test_printf_strings(void) {
    printf("Testing printf strings...\n");

    // Test basic string
    printf("String: %s\n", "Hello");

    // Test empty string
    printf("Empty: '%s'\n", "");

    // Test string with spaces
    printf("Spaces: '%s'\n", "hello world");

    // Test null string (if handled)
    char* null_str = NULL;
    printf("Null: %s\n", null_str ? null_str : "(null)");

    // Test string with special characters
    printf("Special: %s\n", "test!@#$%");

    printf("String test complete\n");
}

void test_printf_hex(void) {
    printf("Testing printf hex...\n");

    // Test lowercase hex
    printf("Lower hex: %x %x %x\n", 0, 255, 4096);

    // Test uppercase hex
    printf("Upper hex: %X %X %X\n", 0, 255, 4096);

    // Test mixed case
    printf("Mixed: %x %X\n", 0xDEAD, 0xBEEF);

    // Test boundary values
    printf("Boundaries: %x %X\n", 0xFFFF, 0x8000);

    // Test with long values
    printf("Long hex: %lx %lX\n", 0x12345678UL, 0x87654321UL);

    printf("Hex test complete\n");
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
    printf("3. Double percent: %%d should show % d literally\n");

    // Test 2: Empty format string
    printf("4. Empty format:\n", 42); // Extra arg should be ignored
    printf("5. Just text, no formats\n");

    // Test 3: Missing arguments (will read garbage - but shouldn't crash)
    printf("6. Missing string: %s\n"); // Will show garbage but not crash
    printf("7. Missing number: %d\n"); // Will show garbage but not crash
}

void test_fputc_file_ops(void) {
    printf("Testing fputc file operations...\n");

    // Test character output to stdout (handle 1)
    FILE* stdout_handle = (FILE*)(uintptr_t)1;
    fputc('A', stdout_handle);
    fputc('B', stdout_handle);
    fputc('\n', stdout_handle);

    // Test newline handling
    fputc('X', stdout_handle);
    fputc('\n', stdout_handle);

    // Test numeric character output
    for (int i = 0; i < 5; i++) {
        fputc('0' + i, stdout_handle);
    }
    fputc('\n', stdout_handle);

    printf("fputc test complete\n");
}

void test_fputs_file_ops(void) {
    printf("Testing fputs file operations...\n");

    // Test string output to stdout (handle 1)
    FILE* stdout_handle = (FILE*)(uintptr_t)1;
    fputs("Hello from fputs\n", stdout_handle);

    // Test empty string
    fputs("", stdout_handle);
    fputs("After empty\n", stdout_handle);

    // Test string with spaces
    fputs("Test string with spaces\n", stdout_handle);

    // Test short strings
    fputs("A\n", stdout_handle);
    fputs("AB\n", stdout_handle);
    fputs("ABC\n", stdout_handle);

    // Test special characters
    fputs("Special: !@#$%\n", stdout_handle);

    printf("fputs test complete\n");
}

void test_stdio() {

    test_stdio_basic();
    test_printf_integers();
    test_printf_strings();
    test_printf_hex();
    test_printf_recursive();
    test_printf_error_conditions();
    test_fputc_file_ops();
    test_fputs_file_ops();

}

#endif

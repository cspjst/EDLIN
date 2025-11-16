#include "tiny_stdio.h"
#include "errno.h"
#include <stdarg.h>

int fputc(int c, FILE* stream) {
    char ch = c;
    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;
    return dos_write_file(fh, 1, &ch, NULL) == DOS_SUCCESS ? ch : (errno = EIO, EOF);
}

static void print_hex(unsigned long val, int uppercase) {
    if (val > 15) {
        print_hex(val >> 4, uppercase);
    }
    int digit = val & 0xF;
    putchar(digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
}

static void print_uint(unsigned long val, int base) {
    if (val >= base) {
        print_uint(val / base, base);
    }
    int digit = val % base;
    putchar(digit < 10 ? '0' + digit : 'A' + digit - 10);
}

static void print_int(long val, int base) {
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    print_uint(val, base);
}

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* p = format;
    while (*p) {
        if (*p == '%') {
            p++;

            // Handle 'l' prefix
            int is_long = 0;
            if (*p == 'l') {
                is_long = 1;
                p++;
            }

            switch (*p) {
                case 'c': {
                    int c = va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    if (!str) str = "(null)";
                    while (*str) putchar(*str++);
                    break;
                }
                case 'd':
                case 'i':
                    if (is_long)
                        print_int(va_arg(args, long), 10);
                    else
                        print_int(va_arg(args, int), 10);
                    break;
                case 'u':
                    if (is_long)
                        print_uint(va_arg(args, unsigned long), 10);
                    else
                        print_uint(va_arg(args, unsigned int), 10);
                    break;
                case 'x':
                    if (is_long)
                        print_hex(va_arg(args, unsigned long), 0);
                    else
                        print_hex(va_arg(args, unsigned int), 0);
                    break;
                case 'X':
                    if (is_long)
                        print_hex(va_arg(args, unsigned long), 1);
                    else
                        print_hex(va_arg(args, unsigned int), 1);
                    break;
                case 'o':
                    if (is_long)
                        print_uint(va_arg(args, unsigned long), 8);
                    else
                        print_uint(va_arg(args, unsigned int), 8);
                    break;
                case '%':
                    putchar('%');
                    break;
                default:
                    putchar('%');
                    putchar(*p);
                    break;
            }
        } else {
            putchar(*p);
        }
        p++;
    }

    va_end(args);
    return 0;
}

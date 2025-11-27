#include "tiny_stdio.h"
#include "tiny_errno.h"
#include "../DOS/dos_services_constants.h"
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

// ======== helper functions ========

static void print_hex(unsigned long val, bool uppercase) {
    if (val > 15) print_hex(val >> 4, uppercase);
    int digit = val & 0xF;
    putchar(digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
}

static void print_uint(unsigned long val, int base) {
    if (val >= base) print_uint(val / base, base);
    int digit = val % base;
    putchar(digit < 10 ? '0' + digit : 'A' + digit - 10);
}

static void print_int(long val, int base) {
    if (val < 0) {
        putchar('-');
        if (val == LONG_MIN) { // avoid overflow
            if (base == 10) {
                print_uint((unsigned long)(-(val + 1)) + 1, 10);
            }
            return;
        }
        val = -val;
    }
    print_uint(val, base);
}

#ifdef TINY_POLICY_STDIO_PRINTF_CAN_FLOAT
static void print_float(double val) {
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    long int_part = (long)val;
    print_int(int_part, 10);
    putchar('.');
    double frac = val - int_part;
    if (frac < 0) frac = -frac;
    long frac_part = (long)(frac * 1000);
    print_int(frac_part, 10);
}
#endif

#ifdef TINY_POLICY_STDIO_PRINTF_CAN_SCIENTIFIC
static void print_scientific(double val, bool uppercase) {
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    int exp = 0;
    while (val >= 10.0) {
        val /= 10.0;
        exp++;
    }
    while (val < 1.0 && val != 0.0) {
        val *= 10.0;
        exp--;
    }
    print_float(val);
    putchar(uppercase ? 'E' : 'e');
    print_int(exp, 10);
}
#endif

// ================

int fputc(int c, FILE* stream) {
    dos_file_handle_t handle = (dos_file_handle_t)(uintptr_t)stream;
    dos_error_code_t dos_err = 0;
    char buffer[2];
    uint16_t nbytes = 1;

    if (c == '\n' && (stream == stdout || stream == stderr)) {
        buffer[0] = '\r';
        buffer[1] = '\n';
        nbytes = 2;
    } else {
        buffer[0] = c;
    }

    __asm {
        .8086
        pushf
        push    ds
        push    si

        mov     bx, handle
        mov     cx, nbytes
        lea     dx, buffer
        mov     ah, DOS_WRITE_FILE_OR_DEVICE_USING_HANDLE
        int     DOS_SERVICE
        jnc     END
        mov     dos_err, ax

END:    pop     si
        pop     ds
        popf
    }

    if (dos_err != 0) {
        errno = dos_to_errno(dos_err);  // set global
        return EOF;
    }

    return (unsigned char)c;
}

int fputs(const char* str, FILE* stream) {
    while (*str) {
        if (fputc(*str++, stream) == EOF) return EOF;
    }
    return 0;
}

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    const char* p = format;
    while (*p) {
        if (*p == '%') {
            p++;

            bool is_long = false;
            if (*p == 'l') {
                is_long = true;
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
                        print_hex(va_arg(args, unsigned long), false);
                    else
                        print_hex(va_arg(args, unsigned int), false);
                    break;
                case 'p':
                case 'X':
                    if (is_long)
                        print_hex(va_arg(args, unsigned long), true);
                    else
                        print_hex(va_arg(args, unsigned int), true);
                    break;

#ifdef TINY_POLICY_STDIO_PRINTF_CAN_OCTAL
                case 'o':
                    if (is_long)
                        print_uint(va_arg(args, unsigned long), 8);
                    else
                        print_uint(va_arg(args, unsigned int), 8);
                    break;
#endif

#ifdef TINY_POLICY_STDIO_PRINTF_CAN_FLOAT
                case 'f':
                    print_float(va_arg(args, double));
                    break;
#endif

#ifdef TINY_POLICY_STDIO_PRINTF_CAN_SCIENTIFIC
                case 'e':
                    print_scientific(va_arg(args, double), false);
                    break;
                case 'E':
                    print_scientific(va_arg(args, double), true);
                    break;
#endif
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

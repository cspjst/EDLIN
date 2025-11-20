#ifndef TINY_STDIO_H
#define TINY_STDIO_H

/**
 * @file tiny_stdio.h
 * @brief Minimal C99 stdio implementation for DOS environments
 *
 * MEMORY SAVING DESIGN:
 * - Direct DOS interrupt calls avoid libc overhead
 * - Macros for simple functions (putc, putchar) eliminate call overhead
 * - No buffering - direct character-by-character I/O
 * - Minimal error checking focused on essential cases
 * - Recursive printf helpers avoid large format string buffers
 * - uint16_t mode parsing in fopen avoids string processing
 *
 * FILE TYPE PUNNING:
 * - FILE is typedef'd as dos_file_handle_t (uint16_t)
 * - fopen returns (FILE*)handle - casting integer to pointer
 * - All functions cast back: (dos_file_handle_t)(uintptr_t)stream
 * - This maintains standard C FILE* interface while using simple integers
 * - stdin/stdout/stderr are handles 0,1,2 cast to FILE*
 *
 * COMPROMISES:
 * - No file buffering (performance tradeoff)
 * - Limited format specifiers in printf
 * - No locale support
 * - Console-only \r\n conversion
 * - 16-bit file positions only
 */

#include "../DOS/dos_services_files.h"
#include <stddef.h>

#define EOF (-1)

#define SEEK_SET FSEEK_SET
#define SEEK_CUR FSEEK_CUR
#define SEEK_END FSEEK_END

typedef dos_file_handle_t FILE;

#define stdin   ((FILE *)0)
#define stdout  ((FILE *)1)
#define stderr  ((FILE *)2)

int fclose(FILE* stream);

int fgetc(FILE* stream);

FILE* fopen(const char* filename, const char* mode);

int fputc(int c, FILE* stream);

int fputs(const char* str, FILE* stream);

size_t fread(void* ptr, size_t size, size_t count, FILE* stream);

int fseek(FILE* stream, long offset, int origin);

long ftell(FILE* stream);

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

int printf(const char* format, ...);

#define putc(c, stream) fputc(c, stream)

#define putchar(c) fputc(c, stdout)

#define puts(str) (fputs(str, stdout), fputc('\n', stdout))

#endif

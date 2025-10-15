/**
 * Syntactic sugar wrappers to shrink memory footprint of DOS executables
 * #include <stdio.h>
 * int fputc(int c, FILE *stream);
 * int fputs(const char *s, FILE *stream);
 * int putc(int c, FILE *stream);
 * int putchar(int c);
 * int puts(const char *s);
 */
#ifndef IOTOOLS_H
#define IOTOOLS_H

#include "strtools.h"
#include "../DOS/dos_services_files.h"

typedef dos_file_handle_t FILE;

int inline fputs(const char* s, FILE* stream) {
    return dos_write_file(*stream, s, cstr_length(s));
}




#endif

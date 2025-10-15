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
#include "../DOS/dos_services_files_constants.h"

#ifdef TFILE
    #error "FILE is already defined!"
#else

typedef struct {
    dos_file_handle_t dos_file_handle;
} TFILE;

static TFILE _DOS_STDIN = { DOS_STDIN_HANDLE };
static TFILE _DOS_STDOUT = { DOS_STDOUT_HANDLE };
static TFILE _DOS_STDERR = { DOS_STDERR_HANDLE };

static TFILE* tstdin = & _DOS_STDIN;
static TFILE* tstdout = & _DOS_STDOUT;
static TFILE* tstderr = & _DOS_STDERR;

#endif

int inline tfputs(const char* s, TFILE* stream) {
    return dos_write_file(stream->dos_file_handle, s, cstr_length(s));
}

int inline tputs(const char* s) {
    return tfputs(s, tstdout);
}

//int inline tfgets()




#endif

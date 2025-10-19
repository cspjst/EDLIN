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

#ifdef tFILE
    #error "tFILE is already defined!"
#else
typedef struct {
    dos_file_handle_t handle;
    int eof;
    int error;
} tFILE;

#ifdef EOF
    #error "EOF is already defined!"
#endif
#define EOF (-1)

#ifdef NULL
    #error "NULL is already defined!"
#endif
#define NULL 0

#define O_TEXT    DOS_STREAM_MODE_TEXT
#define O_BINARY  DOS_STREAM_MODE_BINARY

static tFILE FILE_DOS_STDIN = { DOS_STDIN_HANDLE, 0 };
static tFILE FILE_DOS_STDOUT = { DOS_STDOUT_HANDLE, 0 };
static tFILE FILE_DOS_STDERR = { DOS_STDERR_HANDLE, 0 };

static tFILE* tstdin = &FILE_DOS_STDIN;
static tFILE* tstdout = &FILE_DOS_STDOUT;
static tFILE* tstderr = &FILE_DOS_STDERR;

#endif

int tfputc(int c, tFILE *stream);

int tfputs(const char *s, tFILE *stream);

int tputs(const char *s);

int tfgetc(tFILE *stream);

char* tfgets(char *s, int n, tFILE *stream);

int tfeof(tFILE* stream);

void tclearerr(tFILE* stream);

#endif

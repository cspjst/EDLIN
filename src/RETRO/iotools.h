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
#include <stdbool.h>
#include <stddef.h>

#ifdef FILE
    #error "FILE is already defined!"
#else

typedef struct {
    dos_file_handle_t handle;
    bool eof;
    bool error;
} FILE;

static FILE FILE_DOS_STDIN = { DOS_STDIN_HANDLE, false };
static FILE FILE_DOS_STDOUT = { DOS_STDOUT_HANDLE, false };
static FILE FILE_DOS_STDERR = { DOS_STDERR_HANDLE, false };

static FILE* stdin = & FILE_DOS_STDIN;
static FILE* stdout = & FILE_DOS_STDOUT;
static FILE* stderr = & FILE_DOS_STDERR;

#endif

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *stream);

int fgetc(FILE *stream);

char* fgets(char *s, int n, FILE *stream);

#endif

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

#ifdef FILE
    #error "FILE is already defined!"
#else
typedef struct {
    dos_file_handle_t handle;
    int eof;
    int error;
} FILE;

#ifdef EOF
    #error "EOF is already defined!"
#endif
#define EOF (-1)

#define O_TEXT    DOS_STREAM_MODE_TEXT
#define O_BINARY  DOS_STREAM_MODE_BINARY

static FILE FILE_DOS_STDIN = { DOS_STDIN_HANDLE, 0 };
static FILE FILE_DOS_STDOUT = { DOS_STDOUT_HANDLE, 0 };
static FILE FILE_DOS_STDERR = { DOS_STDERR_HANDLE, 0 };

static FILE* stdin = & FILE_DOS_STDIN;
static FILE* stdout = & FILE_DOS_STDOUT;
static FILE* stderr = & FILE_DOS_STDERR;

#endif

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *stream);

int puts(const char *s);

int fgetc(FILE *stream);

char* fgets(char *s, int n, FILE *stream);

int feof(FILE* stream);

void clearerr(FILE* stream);

int setmode(dos_file_handle_t fhandle, dos_stream_mode_t mode);

#endif

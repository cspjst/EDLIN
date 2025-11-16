#ifndef TINY_STDIO_H
#define TINY_STDIO_H

#include "../DOS/dos_services_files.h"

#define NULL ((void*)0)
#define EOF (-1)

#define SEEK_SET FSEEK_SET
#define SEEK_CUR FSEEK_CUR
#define SEEK_END FSEEK_END

typedef dos_file_handle_t FILE;

#define stdin   ((FILE *)0)
#define stdout  ((FILE *)1)
#define stderr  ((FILE *)2)

int fputc(int c, FILE* stream);

#define putc(c, stream) fputc(c, stream)

#define putchar(c) fputc(c, stdout)

int printf(const char* format, ...);


#endif

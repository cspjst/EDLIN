#ifndef EDLIN_TYPES_H
#define EDLIN_TYPES_H

#include "edlin_constants.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint16_t edlin_size_t;

typedef int fmode_t;

typedef char edlin_line_t[EDLIN_LINE_SIZE];

typedef struct {
    char* filepath;
    bool raw;               // raw binary mode
    edlin_line_t** lines;   // array of pointers to line buffers
    edlin_size_t pos;       // insert position line number
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_file_t;

typedef struct {
    enum_token_t token;
    edlin_size_t pos;
    edlin_size_t argc;
    char* argv[EDLIN_ARGC_MAX];
} edlin_cmd_t;

typedef struct {
    char ascii;
    enum_token_t token;
} edlin_token_t;

#endif

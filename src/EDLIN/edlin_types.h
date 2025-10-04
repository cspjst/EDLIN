#ifndef EDLIN_TYPES_H
#define EDLIN_TYPES_H

#include "edlin_constants.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint16_t edlin_size_t;

// use sequential char values to in-place tokenize and make separating out command types easier using > and <
typedef enum {
    TOK_ERROR = 0,  // error
    // edit command
    TOK_EDIT,       // line# Edit a single line
    // no arg commands
    TOK_HELP,       // ? Show help
    TOK_END,        // E End (save file)
    TOK_QUIT,       // Q Quit (throw away changes)
    // pre command arg(s)
    TOK_APPEND,     // [#lines]A Append a line below the mark
    TOK_COPY,       // [range],toline[,times]C	Copy lines
    TOK_DELETE,     // [range]D Delete lines
    TOK_INSERT,     // [line]I Insert new lines before the mark
    TOK_LIST,       // [range]L	List the file (mark at top unless set elsewhere)
    TOK_MOVE,       // [range],tolineM Move lines
    TOK_PAGE,       // [range]P	Page (same as List, but mark end of list)
    TOK_WRITE,      // [#lines]W Write the file to disk
    // pre & post query commnnd arg(s)
    TOK_REPLACE,    // [range]Rold,new Replace text
    TOK_SEARCH,     // [range]S[string] Search for text
    TOK_QREPLACE,   // [range]?Rold,new Replace text - interactive
    TOK_QSEARCH,    // [range]?S[string] Search for text - interactive
    // pre & post commnnd args
    TOK_TRANSFER,   // [toline]Tfilepath Transfer (insert the contents of a new file at the mark)
    // special cases
    TOK_EMPTY,      // user hit return on whitespace line
    // error states
    TOK_SYNTAX,     // command ok but args wrong
    TOK_UNKNOWN     //
} enum_token_t;

typedef char edlin_line_t[EDLIN_LINE_SIZE];

typedef struct {
    char* filepath;
    bool ignoreCRTLZ;
    edlin_line_t** lines;   // array of pointers to line buffers
    edlin_size_t pos;       // insert position line number
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_file_t;

typedef struct {
    enum_token_t token;
    edlin_size_t argc;
    char* argv[EDLIN_ARGC_MAX];
    bool query;
} edlin_cmd_t;

typedef struct {
    char ascii;
    enum_token_t token;
} edlin_token_t;

#endif

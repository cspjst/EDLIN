#ifndef EDLIN_LOOKUP_TABLE_H
#define EDLIN_LOOKUP_TABLE_H

#include "edlin_types.h"
#include "edlin_tokens.h"

static const edlin_token_t LOOKUP_TOKENS[] = {
    //ch   token         argc    strc     usage
    {'?', TOK_HELP,       0,      0,     "Show help   ?"},
    {'E', TOK_END,        0,      0,     "End         E (save file)"},
    {'Q', TOK_QUIT,       0,      0,     "Quit        Q (throw away changes)"},
    {'A', TOK_APPEND,     1,      0,     "Append      [#lines]A"},
    {'I', TOK_INSERT,     1,      0,     "Insert      [line]I"},
    {'W', TOK_WRITE,      1,      0,     "Write       [#lines]W"},
    {'D', TOK_DELETE,     2,      0,     "Delete      [range]D Delete lines"},
    {'L', TOK_LIST,       2,      0,     "List        [range]L"},
    {'P', TOK_PAGE,       2,      0,     "Page        [range]P"},
    {'C', TOK_COPY,       3,      0,     "Copy        [range][,times]C"},
    {'M', TOK_MOVE,       3,      0,     "Move        [range],tolineM"},
    {'T', TOK_TRANSFER,   1,      1,     "Transfer    [toline]Tfilepath"},
    {'R', TOK_REPLACE,    3,      2,     "Replace     [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,     3,      1,     "Search      [range][?]S[text]"}
};

#endif

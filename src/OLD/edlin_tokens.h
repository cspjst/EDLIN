#ifndef EDLIN_TOKENS_H
#define EDLIN_TOKENS_H

typedef enum {
    TOK_ERROR = 0,  // error
    TOK_QUERY = 0,
    // no arg commands
    TOK_END,        // E End (save file)
    TOK_QUIT,       // Q Quit (throw away changes)
    // single number commands
    TOK_APPEND,     // [#lines]A Append a line below the mark
    TOK_INSERT,     // [line]I Insert new lines before the mark
    TOK_WRITE,      // [#lines]W Write the file to disk
    // range commands
    TOK_DELETE,     // [range]D Delete lines
    TOK_LIST,       // [range]L	List the file (mark at top unless set elsewhere)
    TOK_PAGE,       // [range]P	Page (same as List, but mark end of list)
    // range, numbers commands
    TOK_COPY,       // [range],toline[,times]C	Copy lines
    TOK_MOVE,       // [range],tolineM Move lines
    // single number, payload command
    TOK_TRANSFER,   // [toline]Tfilepath Transfer (insert the contents of a new file at the mark)
    // range, number, payload commands
    TOK_REPLACE,    // [range]Rold,new Replace text
    TOK_SEARCH,     // [range]S[string] Search for text
    // special cases
    TOK_QREPLACE,    // [range]?Rold,new Replace text
    TOK_QSEARCH,     // [range]?S[string] Search for text
    TOK_HELP,
    TOK_EDIT,
    TOK_EMPTY,      // user hit return on whitespace line
    // error states
    TOK_SYNTAX,     // command ok but args wrong
} enum_token_t;

#endif

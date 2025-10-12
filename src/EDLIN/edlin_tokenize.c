#include "edlin_tokenize.h"
#include "edlin_constants.h"
#include "edlin_types.h"
#include "edlin_tokens.h"
#include <ctype.h>
#include <string.h>
//#include <stdio.h>

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

char* edlin_trim_whitespace(char* p) {
    char* q = p;
    while(*p == ' ' || *p == '\t') p++;                         // skip whitespace
    if(p > q) *q = NUL;                                         // null terminate
    return p;
}

// recursively tokenize a comma-separated list of <line>
char* edlin_tokenize_line(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p == ',') {                                             // leading comma -> omitted first field (current line)
        *p = NUL;                                               // empty string token
        cmd->argv[cmd->argc++] = p++;                           // store and advance past comma
    }
    p = edlin_trim_whitespace(p);
    if(
        *p != '.' &&
        *p != '#' &&
        *p != '+' &&
        *p != '-' &&
        !isdigit(*p)
    ) return input;                                             // not a valid <line>
    cmd->argv[cmd->argc++] = p++;                               // store start of <line>
    while(isdigit(*p)) p++;                                     // consume any remainder
    p = edlin_trim_whitespace(p);
    if(*p == ',') {                                             // comma separator -> more fields follow
        *p++ = NUL;                                             // null terminate current field, consume comma
        return edlin_tokenize_line(cmd, p);                     // recurse...
    }
    if(*p == CR || *p == ';') {                                 // end of input
        *p = NUL;                                               // null terminate final field
        if(cmd->argc == 1) cmd->token = TOK_EDIT;               // single number ->  → implicit line edit
    }
    return p;
}

// tokenize ctrl-z separated <string>
char* edlin_tokenize_string(edlin_cmd_t* cmd, char* input, int strc) {
    char * p = input;
    cmd->argv[cmd->argc++] = p;
    while(*p != CTRL_Z && *p != CR) p++;
    *p = NUL;
    if(--strc) {
        p = edlin_tokenize_string(cmd, ++p, strc);
    }
    return p;
}

char* edlin_tokenize_query(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p++ != LOOKUP_TOKENS[TOK_QUERY].ascii) return input;
    for(int i = TOK_REPLACE; i <= TOK_SEARCH; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token + 2;
            *p = *input = NUL;
            return edlin_tokenize_string(cmd, p + 1, LOOKUP_TOKENS[i].strc);
        }
    }
    if(cmd->argc > LOOKUP_TOKENS[TOK_QUERY].argc) cmd->token = TOK_SYNTAX;
    else cmd->token = TOK_HELP;
    return input;
}

char* edlin_tokenize_char(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    for(int i = TOK_END; i <= TOK_SEARCH; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token;
            *p = NUL;
            if(LOOKUP_TOKENS[i].strc) p = edlin_tokenize_string(cmd, p + 1, LOOKUP_TOKENS[i].strc);
            return p;
        }
    }
    return input;
}

char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;                                // series of fall through filters
    memset(cmd, 0, sizeof(edlin_cmd_t));            // zero out the cmd struct
    p = edlin_trim_whitespace(p);                   // scan over any whitespace
    if(*p == CR || *p == NUL) {                     // empty input string
        cmd->token = TOK_EMPTY;
        return p;
    }
    p = edlin_tokenize_line(cmd, p);
    if(cmd->token) return p;
    p = edlin_tokenize_query(cmd, p);
    if(cmd->token) return p;
    p = edlin_tokenize_char(cmd, p);
    if(cmd->token) return p;
    cmd->token = TOK_SYNTAX;
    p++;
    return input;
}

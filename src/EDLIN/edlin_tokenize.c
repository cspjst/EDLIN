#include "edlin_tokenize.h"
#include "edlin_constants.h"
#include "edlin_types.h"
#include "edlin_tokens.h"
#include <ctype.h>
#include <string.h>
//#include <stdio.h>

static const edlin_token_t LOOKUP_TOKENS[] = {
    //ch    token  argc: pre     post      usage
    {'?', TOK_HELP,       0,      0,     "Show help   ?"},
    {'.', TOK_EDIT,       0,      0,     "Edit        . (current line)"},
    {'#', TOK_HASH,       0,      0,     "Edit        # (beyond last line)"},
    {'E', TOK_END,        0,      0,     "End         E (save file)"},
    {'Q', TOK_QUIT,       0,      0,     "Quit        Q (throw away changes)"},
    {'A', TOK_APPEND,     1,      0,     "Append      [#lines]A"},
    {'I', TOK_INSERT,     1,      0,     "Insert      [line]I"},
    {'W', TOK_WRITE,      1,      0,     "Write       [#lines]W"},
    {'L', TOK_LIST,       2,      0,     "List        [range]L"},
    {'P', TOK_PAGE,       2,      0,     "Page        [range]P"},
    {'D', TOK_DELETE,     2,      0,     "Delete      [range]D Delete lines"},
    {'C', TOK_COPY,       3,      0,     "Copy        [range][,times]C"},
    {'M', TOK_MOVE,       3,      0,     "Move        [range],tolineM"},
    {'T', TOK_TRANSFER,   1,      1,     "Transfer    [toline]Tfilepath"},
    {'R', TOK_REPLACE,    3,      2,     "Replace     [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,     3,      1,     "Search      [range][?]S[text]"}
};

char* edlin_trim_whitespace(char* p) {
    char* q = p;
    while(*p == ' ' || *p == '\t') p++;                         // skip leading WS
    if(p > q) *q = NUL;                                         // null-terminate at original start (enables in-place tokenization)
    return p;
}

// recursively tokenize comma-separated <line> tokens (e.g., "1,5" or "+3,-2")
char* edlin_tokenize_line(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p == ',') {                                             // leading comma = omitted first field (current line)
        *p = NUL;                                               // empty token
        cmd->argv[cmd->argc++] = p++;                           // store empty token, advance past comma
    }
    p = edlin_trim_whitespace(p);
    if(
        *p != '.' &&
        *p != '#' &&
        *p != '+' &&
        *p != '-' &&
        !isdigit(*p)
    ) return input;                                             // not a valid <line> token
    cmd->argv[cmd->argc++] = p++;                               // store start of <line> token
    while(isdigit(*p)) p++;                                     // consume numeric suffix
    p = edlin_trim_whitespace(p);
    if(*p == ',') {                                             // comma = more fields follow
        *p++ = NUL;                                             // null-terminate current field
        return edlin_tokenize_line(cmd, p);                     // recurse for next field
    }
    if(*p == ';') {                                             // command separator (no implicit .L)
        *p = NUL;
        return p;
    }
    if(*p == CR || *p == LF || *p == NUL) {                     // true end-of-line
        *p = NUL;
        if(cmd->argc == 1) cmd->token = TOK_EDIT;               // single number → implicit .L (list line)
    }
    return p;
}

// tokenize Ctrl+Z-delimited strings (for R/S commands: "old^Znew^Z")
char* edlin_tokenize_string(edlin_cmd_t* cmd, char* input, int strc) {
    char * p = input;
    for(int i = 1; i <= strc; ++i) {
        cmd->argv[cmd->argc++] = p;                             // store string start
        while(*p != CTRL_Z && *p != CR) p++;                    // find Ctrl+Z or EOL
        *p++ = NUL;                                             // null-terminate string and process next <string> arg
    }
    return p;
}

// handle ?query commands (? alone = help, ?R = replace query, ?S = search query)
char* edlin_tokenize_query(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p++ != '?') return input;                               // must start with '?'
    for(int i = 14; i < 16; ++i) {                             // check ?R and ?S tokens
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token + TOK_QUERY;
            *p = *input = NUL;                                  // null-terminate ? and command char
            return edlin_tokenize_string(cmd, p + 1, LOOKUP_TOKENS[i].strc);
        }
    }
    if(cmd->argc > LOOKUP_TOKENS[0].argc) cmd->token = TOK_SYNTAX;
    else cmd->token = LOOKUP_TOKENS[0].token;                   // ? alone = help
    return input;
}

// handle single-char commands (A, I, D, L, etc.)
char* edlin_tokenize_char(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    for(int i = 1; i < 16; ++i) {                               // skip ? (index 0) and ./# (handled elsewhere)
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token;
            *p = NUL;                                           // null-terminate command char
            if(LOOKUP_TOKENS[i].strc) p = edlin_tokenize_string(cmd, p + 1, LOOKUP_TOKENS[i].strc);
            return p;
        }
    }
    return input;                                               // unknown command char
}

// main tokenizer: whitespace → line tokens → ?query → char commands
char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;
    memset(cmd, 0, sizeof(edlin_cmd_t));                        // clear command struct
    p = edlin_trim_whitespace(char* p)                          // skip leading whitespace
    if(*p == '\n' || *p == NUL) {                               // empty command
        cmd->token = TOK_EMPTY;
        return p;
    }
    p = edlin_tokenize_line(cmd, p);                            // try line number tokens first
    if(cmd->token) return p;                                    // line-only command (e.g., "5" → .L)
    p = edlin_tokenize_query(cmd, p);                           // try ?query commands
    if(cmd->token) return p;
    p = edlin_tokenize_char(cmd, p);                            // try single-char commands
    if(cmd->token) return p;
    cmd->token = TOK_SYNTAX;                                    // unrecognized input
    return input;
}





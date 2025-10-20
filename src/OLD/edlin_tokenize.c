#include "edlin_tokenize.h"
#include "edlin_constants.h"
#include "edlin_types.h"
#include "edlin_tokens.h"
#include "edlin_lookup_table.h"
#include <ctype.h>
#include <string.h>
//#include <stdio.h>

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

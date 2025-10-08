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

// recursively tokenize a comma-separated list of numbers
char* edlin_tokenize_num(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p == ',') {                                             // leading comma -> omitted first field (current line)
        *p = NUL;                                               // empty string token
        cmd->argv[cmd->argc++] = p++;                           // store and advance past comma
    }
    while(*p == ' ' || *p == '\t') p++;                         // skip whitespace
    if(*p != '+' && *p != '-' && !isdigit(*p)) return input;    // not a valid number
    cmd->argv[cmd->argc++] = p++;                               // store start of number
    while(isdigit(*p)) p++;                                     // consume remainder
    if(*p == ',') {                                             // comma separator -> more fields follow
        *p++ = NUL;                                             // null terminate current field, consume comma
        return edlin_tokenize_num(cmd, p);                      // recurse...
    }
    if(*p == CR || *p == ';') {                                 // end of input
        *p = NUL;                                               // null terminate final field
        if(cmd->argc == 1) cmd->token = TOK_EDIT;               // single number ->  → implicit line edit
    }
    return p;
}

// recursively tokenize a comma-separated list of strings ctrl-z or null terminated
char* edlin_tokenize_str(edlin_cmd_t* cmd, char* input) {
    char * p = input;

    return input;
}

char* edlin_tokenize_query(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p++ != '?') return input;
    for(int i = TOK_TRANSFER; i < TOK_SEARCH; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token + TOK_QUERY;
            *p = *input = NUL;
            return edlin_tokenize_str(cmd, p + 1);
        }
    }
    if(cmd->argc > LOOKUP_TOKENS[0].argc) cmd->token = TOK_SYNTAX;
    else cmd->token = LOOKUP_TOKENS[0].token;
    return input;
}

char* edlin_tokenize_char(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    for(int i = 1; i < TOK_TRANSFER; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > LOOKUP_TOKENS[i].argc) cmd->token = TOK_SYNTAX;
            else cmd->token = LOOKUP_TOKENS[i].token;
            *p = NUL;
            if(LOOKUP_TOKENS[i].strc) p = edlin_tokenize_str(cmd, p + 1);
            return p;
        }
    }
    return input;
}


char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;                                // series of fall through filters
    memset(cmd, 0, sizeof(edlin_cmd_t));            // zero out the cmd struct
    while(*p == ' ' || *p == '\t') p++;             // scan over any whitespace
    if(*p == '\n' || *p == NUL) {                   // empty input string
        cmd->token = TOK_EMPTY;
        return p;
    }
    p = edlin_tokenize_num(cmd, p);
    if(cmd->token) return p;
    p = edlin_tokenize_query(cmd, p);
    if(cmd->token) return p;
    p = edlin_tokenize_char(cmd, p);
    if(cmd->token) return p;
    cmd->token = TOK_SYNTAX;
    p++;
    return input;
}

/*

char* edlin_tokenize_dot(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(*p != '.') return input;
    cmd->argv[0] = p++;
    cmd->argc = 1;
    char* q = p;
    while(*p == ' ' || *p == '\t') p++;                         // skip whitespace
    if(*p == CR || *p == ';') {
        cmd->token = TOK_EDIT;
        *q = NUL;
        return p;
    }
    return input;
}

// end, quit - no arguemnts
char* edlin_tokenize_EQ(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    for(int i = 1; i < 3; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc) cmd->token = TOK_SYNTAX;              // quit and end have no args
            else cmd->token = LOOKUP_TOKENS[i].token;
            *p = NUL;
            return p;
        }
    }
    return input;
}

char* edlin_tokenize_T(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    if(toupper(*p) != 'T') return p;
    if(cmd->argc > 1) cmd->token = TOK_SYNTAX;                  // too many args
    else cmd->token = TOK_TRANSFER;
    *p++ = NUL;
    if(*p == CR || *p == CTRL_Z) {
        cmd->token = TOK_SYNTAX;                                // no payload
        return p;
    }
    cmd->argv[cmd->argc++] = p;
    while(*p != CR && *p != CTRL_Z) p++;
    // TODO: handle CTRL-V to enter ctrl codes
    *p = NUL;
    return p;
}

// append, write, insert - 1 optional number
char * edlin_tokenize_AWI(edlin_cmd_t* cmd, char* input) {
    char * p = input;
    for(int i = 3; i < 6; ++i) {
        if(toupper(*p) == LOOKUP_TOKENS[i].ascii) {
            if(cmd->argc > 1) cmd->token = TOK_SYNTAX;          // too many args
            else cmd->token = LOOKUP_TOKENS[i].token;
            *p = NUL;
            return p;
        }
    }
    return input;
}

 */

/*
char* edlin_pre_args(edlin_cmd_t* cmd, char* p, char* p0) {
    return p;
    int j = 0;                              // j arg counter
    if(p == p0) return p;                   // no pre args
    *p = NUL;                               // null terminate
    // tokenize CSV list of args
    if(*p0 == ',') {                        // check for current line syntax
        cmd->argv[j++] = p0++;              // store pointer to arg
    }
    char * arg = strtok(p0, ",");           // tokenize by CSV
    while (arg != NULL && j < EDLIN_ARGC_MAX) {
        cmd->argv[j++] = arg;               // store pointer to arg
        arg = strtok(NULL, ",");            // get next token
    }
    cmd->argc = j;                          // store argc
    return p++;
}

char* edlin_post_args(edlin_cmd_t* cmd, char* input) {
    return input;
}

char* edlin_tokenize_SRT(edlin_cmd_t* cmd, char* input) {
    **** have to scan ahead
    char* p = input;
    if(*p == '?') {
        *p = NUL;
        p++;
        switch(toupper(*p)) {
        case'R':
            cmd->token = TOK_QREPLACE;
            return edlin_post_args(cmd, edlin_pre_args(cmd, p, input));
        case'S':
            cmd->token = TOK_QSEARCH;
            return edlin_post_args(cmd, edlin_pre_args(cmd, p, input));
        default:
            cmd->token = TOK_HELP;
            return p;
        }
    }
    switch(toupper(*p)) {
    case'R':
        cmd->token = TOK_REPLACE;
        return edlin_post_args(cmd, edlin_pre_args(cmd, p, input));
    case'S':
        cmd->token = TOK_SEARCH;
        return edlin_post_args(cmd, edlin_pre_args(cmd, p, input));
    case'T':
        cmd->token = TOK_TRANSFER;
        return edlin_post_args(cmd, edlin_pre_args(cmd, p, input));
    default:
        p++;
    }
    return input;
}

char* edlin_tokenize_edit(edlin_cmd_t* cmd, char* p) {
    if(!isdigit(*p) && *p != '.') return p;         // valid chars digit, '.'
    cmd->token = TOK_EDIT;                          // found a digit or '.'
    cmd->argc = 1;                                  // 1 arg
    cmd->argv[0] = p;                               // store ptr to arg
    while(isdigit(*p)) p++;                         // scan until no more digits
    if(*p == '.' && p == cmd->argv[0]) p++;         // scan past '.'
    if(*p == ';') *p = NUL;                         // null terminate the arg data
    if(*p == NUL) return p;                         // success
    cmd->token = TOK_SYNTAX;                        // otherwise syntax error
    return p;
}
 */

/*
void edlin_inplace_tokenize(char *p) {
    while(*p) {
        if(*p == '?') {
            *p++ = TOK_QUERY;                       // assume interactive
            switch(toupper(*p)) {
            case'R':
                *p = TOK_REPLACE;
                while(*p && *p != '\x1A') p++;      // skip past replace args
                continue;
            case'S':
                *p = TOK_SEARCH;
                while(*p && *p != '\x1a') p++;      // skip past search arg
                if(*p == '\x1a') p++;
                continue;
            default:
                *(p - 1) = TOK_HELP;
                continue;
            }
        }
        for(int i = 1; i < 13; ++i) {

        }
        p++;
    }
}
*/

/*
char* tokenize_post_args (edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;           // scan over until candidate char
    if(*p == ';') return p0;
    for(int i = 8; i < 11; ++i) { // R,S,T search
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {
            int j = 0;                              // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            *p = '\0';                              // replace with end args
            if(p0 < p) { // has pre args
                if(*(p - 1) == '?')  cmd->query = true;
                // tokenize CSV list of pre args
                if(*p0 == ',') {                        // check for current line syntax
                    cmd->argv[j++] = p0++;              // store pointer to arg
                }
                char * arg = strtok(p0, ",?");       // tokenize by CSV, CTRL-Z
                while (arg != NULL && j < EDLIN_ARGC_MAX) {
                    cmd->argv[j++] = arg;               // store pointer to arg
                    arg = strtok(NULL, ",?");        // get next token
                }
            }
            // tokenize CSV list of post args
            char * arg = strtok(++p, ",\x1A\n");       // tokenize by CSV, CTRL-Z
            while (arg != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = arg;               // store pointer to arg
                arg = strtok(NULL, ",\x1A\n");        // get next token
            }
            cmd->argc = j;                          // store argc
            while(*p != '\0' && *p != '\x1A') p++;  // scan to ctrl-z or \n
            return p;                               // update input ptr
        }
    }
    return p0;
}

char* tokenize_pre_args(edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;                        // scan over until candidate char
    for(int i = 0; i < 8; ++i) {           // search the char table
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {  // valid comand char
            int j = 0;                              // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            if(p == p0) return p;                   // no pre args
            *p = '\0';                              // replace with end args
            // tokenize CSV list of args
            if(*p0 == ',') {                        // check for current line syntax
                cmd->argv[j++] = p0++;              // store pointer to arg
            }
            char * arg = strtok(p0, ",");           // tokenize by CSV
            while (arg != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = arg;               // store pointer to arg
                arg = strtok(NULL, ",");            // get next token
            }
            cmd->argc = j;                          // store argc
            return p;                               // update input ptr
        }
    }
    return p0;                                      // next filter
}

char* tokenize_no_args(edlin_cmd_t* cmd, char* p) {
    char* p0 = p;
    while(isspace(*p) || *p == ',' || *p == ';') p++;
    switch(*p) {                                    // handle valid no arg commands
    case'?':
        cmd->token = TOK_HELP;
        return p;
    case'e':
    case'E':
        cmd->token = TOK_END;
        return p;
    case'q':
    case'Q':
        cmd->token = TOK_QUIT;
        return p;
    default:
        return p0;                                   // no valid chars
    }
}

char* tokenize_edit(edlin_cmd_t* cmd, char* p) {
    if(!isdigit(*p) && *p != '.') return p;         // invalid chars
    cmd->token = TOK_EDIT;                          // found a digit
    cmd->argc = 1;                                  // 1 arg
    cmd->argv[0] = p;                               // store ptr to arg
    while(isdigit(*p)) p++;                         // scan until no more digits
    if(*p == ';' || *p == '\n') *p = '\0';          // end the arg data
    else cmd->token = TOK_ERROR;                    // otherwise syntax error
    return p;                                       // success
}
*/

/*
    //p = tokenize_post_args(cmd, p);                 // ?R,?S,T
    if(cmd->token) return p;                        // yes
   // p = tokenize_pre_args(cmd, p);                  // A,D,I,L,M,P,W
    if(cmd->token) return p;                        // yes
    p = tokenize_no_args(cmd, p);                   // ?,E,Q
    if(cmd->token) return p;                        // yes

    return tokenize_edit(cmd, p);                   // line edit or error
 */
/*
 * p0++;                       // no pre args
 else {
     *p = ',';                          // replace so CSV pre and post
     if(*(p - 1) == '?') cmd->query = true;
 }
 // tokenize CSV list of args
 if(*p0 == ',') {                        // check for current line syntax
     cmd->argv[j++] = p0++;              // store pointer to arg
 }
 char * arg = strtok(p0, ",?\x1A\n");       // tokenize by CSV, CTRL-Z
 while (arg != NULL && j < EDLIN_ARGC_MAX) {
     cmd->argv[j++] = arg;               // store pointer to arg
     arg = strtok(NULL, ",?\x1A\n");        // get next token
 }
 cmd->argc = j;                          // store argc
 while(*p != '\x1A' && *p != '\n') p++;  // scan to ctrl-z or \n
 return p;                               // update input ptr
 *
 */

#ifndef EDLIN_CONSTANTS_H
#define EDLIN_CONSTANTS_H

// ASCII control codes
#define NUL     '\0'
#define CR      '\x0D'
#define CTRL_C  '\x03'      // ETX  edlin uses to end insert mode
#define CTRL_V  '\x16'      // SYN  edlin uses to encode control chars
#define CTRL_Z  '\x1A'      // SUB  edlin uses to mark end for search and replace

#define EDLIN_LINE_SIZE     256
#define EDLIN_MAX_LINES     65534
#define EDLIN_PAGE_SIZE     23
#define EDLIN_ARGC_MAX      5
#define EDLIN_CMD_COUNT     17

#endif

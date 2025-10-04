#ifndef EDLIN_DEBUG_H
#define EDLIN_DEBUG_H

#include "edlin_errors.h"
#include "edlin_types.h"
#include <stdio.h>

void debug_file_t(edlin_file_t* file) {
    printf("file %s\nctrl-z %u\npos %u\nsize %u\ncapacity %u\n",
        file->filepath,
        file->ignoreCRTLZ,
        file->pos,
        file->size,
        file->capacity
    );
}

void debug_cmd_t(edlin_cmd_t* cmd) {
    printf("token=%i argc=%i %c args: ", cmd->token, cmd->argc, cmd->query ?'?' :'-');
    for(int i = 0; i < cmd->argc; ++i) {
        printf(">%s< ", cmd->argv[i]);
    }
    printf("\n");
}

#endif

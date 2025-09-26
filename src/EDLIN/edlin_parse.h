#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

#include "edlin_types.h"
#include <stdbool.h>

// handler function signature for dispatch table
typedef bool (*edlin_fn_command_t)(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_parse(edlin_cmd_t* cmd, edlin_file_t* file);

// handler functions:
bool edlin_fn_edit(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_help(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_end(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_quit(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_append(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_copy(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_delete(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_insert(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_list(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_move(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_page(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_write(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_replace(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_search(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_transfer(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_error(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_empty(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_fn_unknown(edlin_cmd_t* cmd, edlin_file_t* file);

#endif

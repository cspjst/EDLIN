#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

#include "edlin_types.h"
#include <stdbool.h>

// handler function signature for dispatch table
typedef bool (*edlin_fn_command_t)(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_parse(edlin_cmd_t* cmd, edlin_file_t* file);

// no arg commands
bool edlin_fn_end(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_quit(edlin_cmd_t* cmd, edlin_file_t* file);

// single number commands
bool edlin_fn_append(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_insert(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_write(edlin_cmd_t* cmd, edlin_file_t* file);

// single number commands
bool edlin_fn_delete(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_list(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_page(edlin_cmd_t* cmd, edlin_file_t* file);

// range, numbers commands
bool edlin_fn_copy(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_move(edlin_cmd_t* cmd, edlin_file_t* file);

// single number, payload command
bool edlin_fn_transfer(edlin_cmd_t* cmd, edlin_file_t* file);

// range, number, payload commands
bool edlin_fn_replace(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_search(edlin_cmd_t* cmd, edlin_file_t* file);

// special cases
bool edlin_fn_qreplace(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_qsearch(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_help(edlin_cmd_t* cmd, edlin_file_t* file);
bool edlin_fn_edit(edlin_cmd_t* cmd, edlin_file_t* file);

#endif

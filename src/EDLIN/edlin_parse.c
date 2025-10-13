#include "edlin_parse.h" 
#include "edlin_tokens.h"
#include "edlin_lookup_table.h"

// dispatch table 
static const edlin_fn_command_t EDLIN_DISPATCH[] = {
    // no arg commands
    [TOK_END]     = edlin_fn_end,       // 1  E  End (save file)
    [TOK_QUIT]    = edlin_fn_quit,      // 2  Q  Quit (throw away changes)
    // single number commands
    [TOK_APPEND]  = edlin_fn_append,    // 3  [#lines]A  Append a line below the mark
    [TOK_INSERT]  = edlin_fn_insert,    // 4  [line]I    Insert new lines before the mark
    [TOK_WRITE]   = edlin_fn_write,     // 5  [#lines]W  Write the file to disk
    // single number commands
    [TOK_DELETE]  = edlin_fn_delete,    // 6  [range]D  Delete lines
    [TOK_LIST]    = edlin_fn_list,      // 7  [range]L  List the file (mark at top unless set elsewhere)
    [TOK_PAGE]    = edlin_fn_page,      // 8  [range]P  Page (same as List, but mark end of list)
    // range, numbers commands
    [TOK_COPY]    = edlin_fn_copy,      // 9  [range],toline[,times]C	  Copy lines
    [TOK_MOVE]    = edlin_fn_move,      // 10 [range],tolineM           Move lines 
    // single number, payload command
    [TOK_TRANSFER] = edlin_fn_transfer, // 11 [toline]Tfilepath    Transfer (insert the contents of a new file at the mark)
    // range, number, payload commands
    [TOK_REPLACE] = edlin_fn_replace,   // 12 [range]Rold,new      Replace text
    [TOK_SEARCH]  = edlin_fn_search,    // 13 [range]S[string]     Search for text
    // special cases
    [TOK_QREPLACE] = edlin_fn_qreplace, // 14 [range]?Rold,new     Replace text interactive
    [TOK_QSEARCH]  = edlin_fn_qsearch,  // 15 [range]?S[string]    Search for text interavctive
    [TOK_HELP]    = edlin_fn_help,      // 16 ?                    Help command
    [TOK_EDIT]    = edlin_fn_edit,      // 17 [#line], '.' or '#'  Edit a line
   
};

bool edlin_parse(edlin_cmd_t* cmd, edlin_file_t* file) {
    edlin_fn_command_t fn = EDLIN_DISPATCH[cmd->token - 1];
    return fn(cmd, file);
}

// no arg commands
bool edlin_fn_end(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_quit(edlin_cmd_t* cmd, edlin_file_t* file) {
    return !wait_yesno("Abort edit");
}

 // single number commands
bool edlin_fn_append(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_insert(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_write(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

// range, numbers commands
bool edlin_fn_delete(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_list(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_page(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

// range, numbers commands
bool edlin_fn_copy(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_move(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

// single number, payload command
bool edlin_fn_transfer(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

// single number, payload command
bool edlin_fn_replace(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_search(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

// special cases
bool edlin_fn_qreplace(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_qsearch(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_help(edlin_cmd_t* cmd, edlin_file_t* file) {
    for(int i = 0; i < EDLIN_CMD_COUNT; ++i) {
        printf("%s\n", LOOKUP_TOKENS[i].usage);
    }
    return true;
}

bool edlin_fn_edit(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}



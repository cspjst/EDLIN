#ifndeF EDLIN_DISPATCH_TABLE_H
#define EDLIN_DISPATCH_TABLE_H

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

#endif

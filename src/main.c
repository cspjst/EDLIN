#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_debug.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    edlin_line_t input;
    edlin_cmd_t cmd;
    edlin_file_t* file = edlin_new_file();
    edlin_intro();
    if (file && edlin_config(argc, argv, file)) {
        edlin_read_line(&input, stdin);
        char* p = input;
        while(cmd.token != TOK_EMPTY) {
            p = edlin_tokenize(&cmd, p);
            debug_cmd_t(&cmd);
            if(cmd.token == TOK_SYNTAX) {
                edlin_panic(EDLIN_ERR_ENTRY, "");
                break;
            }
            p++;
        }
    }

    edlin_free_file(file);

    return EXIT_SUCCESS;
}

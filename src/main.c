#include "RETRO/iotools.h"

int main(int argc, char* argv[]) {
    char buffer[] = "hello   ";
    tfputs(&buffer[2], tstdout);
    tputs("world\n");
}


/*
#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_parse.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_debug.h"
//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>


#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main(int argc, char* argv[]) {
    edlin_line_t input;
    edlin_cmd_t cmd;
    edlin_file_t* file = edlin_new_file();
    // Set stdin to binary mode
    setmode(fileno(stdin), O_BINARY);
    if (file && edlin_config(argc, argv, file)) {
        debug_file_t(file);
        while(file->open) {
            printf("*");
            edlin_read_line(&input, stdin);
            char* p = input;
            while(cmd.token != TOK_EMPTY) {
                p = edlin_tokenize(&cmd, p);
                if(cmd.token == TOK_SYNTAX) {
                    edlin_panic(EDLIN_ERR_ENTRY);
                    break;
                }
                edlin_parse(&cmd, file);
                debug_cmd_t(&cmd);
                p++;
            }
            cmd.token = 0;
        }
    }

    edlin_free_file(file);

    return EXIT_SUCCESS;
}
*/

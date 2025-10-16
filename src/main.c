#include "RETRO/iotools.h"

int main(int argc, char* argv[]) {
    char buffer[] = "hello world\n\r";
     int c;
     fputc('.', stdout);
     fputc('\n', stdout);
     fputs(buffer, stdout);
     c = fgetc(stdin);
     fputc(c, stdout);
     fputc('\n', stdout);
     fputs("Read error\n\r", stderr);
     // Echo lines from stdin to stdout until EOF or empty line
     while (true) {
         if (!fgets(buffer, sizeof(buffer), stdin)) {
             if (stdin->error) {
                 fputs("Read error\n\r", stderr);
                 break;
             }
             // EOF reached
             break;
         }

         // Check for empty line (user pressed Enter with no input)
         if (buffer[0] == '\n' || buffer[0] == '\0') {
             break;
         }

         // Echo back
         if (fputs(buffer, stdout) == EOF) {
             if (stdout->error) {
                 fputs("Write error\n\r", stderr);
                 break;
             }
         }

         // Optional: echo a single char to test fputc
         fputc('.', stdout);
         fputc('\n', stdout);
     }

     // Final status
     fputs("Done.\n", stdout);
     return 0;
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

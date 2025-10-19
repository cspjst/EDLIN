
#include "TOOLS/iotools.h"

int main() {
    tputs("Type CTRL-Z: ");

    int c = tfgetc(tstdin);

    if (c == 0x1A) {
        tputs("SUCCESS: Got CTRL-Z (0x1A) - not EOF!");
    } else if (c == EOF) {
        tputs("FAIL: CTRL-Z caused EOF");
    } else {
        tputs("Got something else");
    }

    tputs("Now type something after CTRL-Z: ");
    c = tfgetc(tstdin);

    if (c != EOF) {
        tputs("SUCCESS: Can read after CTRL-Z!");
    } else {
        tputs("FAIL: EOF after CTRL-Z");
    }

    return 0;
}

/*
#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_parse.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_debug.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    edlin_line_t input;
    edlin_cmd_t cmd;
    edlin_file_t* file = edlin_new_file();
    //setmode(fileno(stdin), O_BINARY);
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

    //return EXIT_SUCCESS;
}

/*
int main(int argc, char* argv[]) {
    char buffer[] = "hello world\n\r";
     int c;
     fputc('.', stdout);
     fputc('\n', stdout);
     fputs(buffer, stdout);
     c = fgetc(stdin);
     fputc(c, stdout);
     fputc('\n', stdout);
     fputs("stderr some dreadful error\n\r", stderr);
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

int main(void) {
    char buffer[16];

    // Test decimal
    cstr_int_to_alpha(123, buffer, 10);
    fputs("123 in base 10: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    // Test negative decimal
    cstr_int_to_alpha(-456, buffer, 10);
    fputs("-456 in base 10: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    // Test hex
    cstr_int_to_alpha(255, buffer, 16);
    fputs("255 in base 16: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    // Test binary
    cstr_int_to_alpha(10, buffer, 2);
    fputs("10 in base 2: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    // Test zero
    cstr_int_to_alpha(0, buffer, 10);
    fputs("0 in base 10: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    // Test INT_MIN (edge case)
    cstr_int_to_alpha(-32768, buffer, 10);
    fputs("INT_MIN in base 10: ", stdout);
    fputs(buffer, stdout);
    fputc('\n', stdout);

    return 0;
}

*/
/*
#include <assert.h>

int main(void) {
    char buf[20];
    dos_file_handle_t h = 3;//stdin->handle;

    // Save original mode
    uint16_t orig_info = dos_get_device_info(h);
    cstr_int_to_alpha(orig_info, buf, 2);
    puts(buf);
    dos_stream_mode_t orig_mode = (orig_info & DOS_DEV_BINARY)
                                  ? DOS_STREAM_MODE_BINARY
                                  : DOS_STREAM_MODE_TEXT;

    // Set to binary
    assert(dos_set_stream_mode(h, DOS_STREAM_MODE_BINARY) == 0);
    //setmode(fileno(stdin), O_TEXT);
    uint16_t info1 = dos_get_device_info(h);
    cstr_int_to_alpha(info1, buf, 2);
    puts(buf);
    assert((info1 & DOS_DEV_BINARY) != 0);  // bit 7 set

    // Set to text
    assert(dos_set_stream_mode(h, DOS_STREAM_MODE_TEXT) == 0);
    //setmode(fileno(stdin), O_BINARY);
    uint16_t info2 = dos_get_device_info(h);
    cstr_int_to_alpha(info2, buf, 2);
    puts(buf);
    assert((info2 & DOS_DEV_BINARY) == 0);  // bit 7 clear

    // Restore original mode
    assert(dos_set_stream_mode(h, orig_mode) == 0);

    // Optional: show final state

    cstr_int_to_alpha(dos_get_device_info(h), buf, 2);
    fputs("Final device info (binary): ", stdout);
    fputs(buf, stdout);
    fputc('\n', stdout);

    return 0;
}
*/


#include "STR/str_fixed.h"
#include "STR/str_types.h"
#include <stddef.h>

int main() {
    str_fixed_t str, str2;
    str_fixed_t input, prompt;

    str_stdout(str_cstr(&prompt, "TEST2: Enter char: "));
    str_stdin(&input);
    str_stdout(str_cstr(&str, "Got: "), &input, CRLF);


    // Chain creation and output
    str_stdout(str_cstr(&str, "Hello\r\n"));

    // Chain integer conversion
    str_stdout(str_int(&str2, -12345, 10), CRLF);
    str_trim_right(&str, "\r\n");
    str_stderr(&str, &str2, CRLF);

    // Chain case conversion
    str_stdout(str_to_upper(str_cstr(&str, "mixed case")), CRLF);
    str_stdout(str_to_lower(&str), CRLF);

    // Chain trimming
    str_stdout(str_trim(str_cstr(&str, "  spaces  ")," "));

    // Chain reverse
    str_stdout(str_reverse(str_cstr(&str, "reverse")), CRLF);

    // Multiple chains
    str_stdout(str_int(str_cstr(&str, "Hex: "), 255, 16), CRLF);

    // Copy chain
    str_stdout(str_str(&str2, str_cstr(&str, "copied")), CRLF);

    // Complex chain - trim, upper, reverse
    //str_stdout(str_reverse(str_to_upper(str_trim(str_cstr(&str, "  hello  ")))), CRLF);

    // stdin with prompt chain
    str_stdin_prompt(str_cstr(&prompt, "Enter text: "), &input);
    str_stdout(str_cstr(&str, "You entered: "), &input, CRLF);

   // str_stdout(str_cstr(&str, "TEST3: Press any key: "));
   // dos_read_file(STDIN, &c, 1);

    return 0;
}

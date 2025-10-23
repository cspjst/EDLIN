
#include "STR/str_fixed.h"
#include <stddef.h>

int main() {
    str_fixed_t str, str2;
    
    // Chain creation and output
    str_stdout(str_cstr(&str, "Hello"));
    str_stdout(&CRLF);
    
    // Chain integer conversion
    str_stdout(str_int(&str, -12345, 10), CRLF);
    
    // Chain case conversion
    str_stdout(str_to_upper(str_cstr(&str, "mixed case")), CRLF);
    
    // Chain trimming
    str_stdout(str_trim(str_cstr(&str, "  spaces  ")), CRLF);
    
    // Chain reverse
    str_stdout(str_reverse(str_cstr(&str, "reverse")), CRLF);
    
    // Multiple chains
    str_stdout(str_int(str_cstr(&str, "Hex: "), 255, 16), CRLF);
    
    // Copy chain
    str_stdout(str_str(&str2, str_cstr(&str, "copied")), CRLF);
    
    // Complex chain - trim, upper, reverse
    str_stdout(str_reverse(str_to_upper(str_trim(str_cstr(&str, "  hello  ")))), CRLF);
    
    // stdin with prompt chain
    str_fixed_t input, prompt;
    str_stdin_prompt(str_cstr(&prompt, "Enter text: "), &input);
    str_stdout(str_cstr(&str, "You entered: "), &input, CRLF);
    
    return 0;
}

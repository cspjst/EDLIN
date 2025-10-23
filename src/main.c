
#include "STR/str_fixed.h"
#include <stddef.h>

int main() {
    str_fixed_t str, str2;
    
    // Test string creation and output
    str_cstr(&str, "  Hello World!  ");
    str_stdout(&str);
    str_stdout(&CRLF);
    
    // Test integer conversion
    str_int(&str, -12345, 10);
    str_stdout(&str);
    str_stdout(&CRLF);
    
    // Test case conversion
    str_cstr(&str, "MiXeD CaSe");
    str_stdout(&str);
    str_stdout(&CRLF);
    str_to_upper(&str);
    str_stdout(&str);
    str_stdout(&CRLF);
    
    // Test trimming
    str_cstr(&str, "  spaces around  ");
    str_stdout(&str);
    str_stdout(&CRLF);
    str_trim(&str);
    str_stdout(&str);
    str_stdout(&CRLF);
    
    // Test reverse
    str_cstr(&str, "reverse");
    str_stdout(&str);
    str_stdout(&CRLF);
    str_reverse(&str);
    str_stdout(&str);
    str_stdout(&CRLF);
    
    // Test copy
    str_cstr(&str, "original");
    str_str(&str2, &str);
    str_stdout(&str2);
    str_stdout(&CRLF);
    
    return 0;
}

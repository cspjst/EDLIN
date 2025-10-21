
int main() {
    str_fixed_t str;
    
    // Test successful conversion
    str_print(&(str_fixed_t){"Testing itoa:", 13, 0});
    str_itoa(12345, &str, 10);
    str_println(&str);
    
    str_itoa(-6789, &str, 10); 
    str_println(&str);
    
    str_itoa(255, &str, 16);
    str_println(&str);
    
    // Test error cases
    str_error_t err = str_itoa(99999, &str, 10);
    if (err != STR_SUCCESS) {
        str_print_error(err);
    }
    
    err = str_itoa(123, NULL, 10);
    if (err != STR_SUCCESS) {
        str_print_error(err);
    }
    
    return 0;
}

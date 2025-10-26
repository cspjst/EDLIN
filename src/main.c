#include "MEM/mem_constants.h"
#include "MEM/mem_types.h"
#include "STR/dos_string.h"
#include "MEM/mem_tools.h"
#include "STR/dos_string_types.h"

int main() {
    str_fixed_t msg, num;
    str_int(&num, mem_get_free_bytes(), 10);
    str_stdout(&num, CRLF);
    str_int(&num, mem_get_startup_bytes(), 10);
    str_stdout(&num, CRLF);
    str_int(&num, mem_get_startup_bytes() - mem_get_free_bytes(), 10);
    str_stdout(&num, CRLF);

}

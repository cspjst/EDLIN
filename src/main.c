#include "STR/dos_string.h"
#include "MEM/mem_tools.h"
#include "EDLIN/edlin_line_pool.h"

int main() {
    str_out(as_dec(mem_get_free_bytes()), CRLF);
    str_out(as_dec(mem_get_startup_bytes()), CRLF);
    str_out(as_dec(mem_get_startup_bytes() - mem_get_free_bytes()), CRLF);

}

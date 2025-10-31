#include "DOS/dos_services_files_types.h"
#include "STR/dos_string.h"
#include "DOS/dos_services_files.h"

int main() {
    str_fixed_t file_path;
    str_in_prompt(cstr("Enter file name: "), &file_path);

    str_out(as_hex(dos_get_file_attributes(file_path.text)), CRLF);
    str_out(as_dec(dos_errno()), CRLF);

    str_out(as_hex(dos_set_file_attributes(file_path.text, 0)), CRLF);
    str_out(as_dec(dos_errno()), CRLF);
}

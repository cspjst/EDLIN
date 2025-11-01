#include "DOS/dos_error_types.h"
#include "DOS/dos_services_files_types.h"
#include "STR/dos_string.h"
#include "DOS/dos_services_files.h"

int main() {
    str_fixed_t file_path;
    str_in_prompt(cstr("Enter file name: "), &file_path);


}

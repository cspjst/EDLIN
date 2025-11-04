#include "dos_file_tools.h"
#include "dos_services_files.h"

uint8_t dos_file_exists(const char* path_name) {
    dos_file_attributes_t attr;
    return dos_get_file_attributes(path_name, &attr) == 0;
}

uint8_t dos_file_is_eof(dos_file_handle_t fhandle) {

}

dos_file_size_t dos_file_size(const char* path_name) {

}

char* dos_file_ext(const char* path_name) {

}

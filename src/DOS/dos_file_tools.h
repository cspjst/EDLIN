#ifndef DOS_FILE_TOOLS_H
#define DOS_FILE_TOOLS_H

#include "dos_services_files_types.h"
#include <stdint.h>

uint8_t dos_file_exists(const char* path_name);

uint8_t dos_file_is_eof(dos_file_handle_t fhandle);

dos_file_size_t dos_file_size(dos_file_handle_t fhandle);

char* dos_file_ext(const char* path_name);

#endif

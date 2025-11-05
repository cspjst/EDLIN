#include "dos_file_tools.h"
#include "dos_services_files.h"

uint8_t dos_file_exists(const char* path_name) {
    dos_file_attributes_t attr;
    return dos_get_file_attributes(path_name, &attr) == 0;
}

uint8_t dos_file_is_eof(dos_file_handle_t fhandle) {
    if (fhandle == 0xFFFF) return 1;                                              // invalid handle = EOF
    dos_file_position_t size = 0;
    dos_file_position_t p;                                                     
    if(dos_move_file_pointer(fhandle, 0, FSEEK_CUR, &p) != 0) return 1;           // save current position
    if(dos_move_file_pointer(fhandle, 0, 2, &size) != 0) return 1;                // get file size (seek to end)
    if(dos_move_file_pointer(fhandle, p, FSEEK_SET, NULL) return 1;               // restore original position
    return (p >= file_size);                                                      // dual-seek method for reliable EOF detection
}

dos_file_size_t dos_file_size(dos_file_handle_t fhandle) {
    dos_file_size_t size = 0;
    dos_file_position_t p;
    dos_move_file_pointer(fhandle, 0, FSEEK_CUR, &p);                             // save current position
    dos_error_code_t err = dos_move_file_pointer(fhandle, 0, FSEEK_END, &size);   // seek to the end
    if (err != 0) size = 0;                                                       // error size = 0
    dos_move_file_pointer(fhandle, p, FSEEK_SET, NULL);                           // restore original position
    return size;
}

char* dos_file_ext(const char* path_name) {
    if (!path_name || !path_name[0]) return NULL;
    const char* dot = NULL;
    const char* p = path_name;    
    while (*p) if (*p == '.') dot = p++;                                          // scan for last '.'
    return (dot && *(dot + 1)) ? dot + 1 : NULL;                                  // return pointer to extension (character after last dot) or NULL
}

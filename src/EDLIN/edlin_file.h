#ifndef EDLIN_EDIT_H
#define EDLIN_EDIT_H

#include "edlin_types.h"
#include "../DOS/dos_services_files.h"

edlin_file_t* edlin_new_file();

void edlin_free_file(edlin_file_t* file);

edlin_line_t* edlin_new_line();

bool edlin_read_line(edlin_line_t* line, FILE* istream);

bool edlin_load_file(edlin_file_t* file);

void edlin_print_file(edlin_file_t* file);

#endif

#ifndef EDLIN_EDIT_H
#define EDLIN_EDIT_H

#include "edlin_types.h"
#include <stdbool.h>

edlin_file_t* edline_new_file(const edlin_line_t* path, edlin_size_t capacity);

void edlin_free_file(edlin_file_t* file);

bool edlin_init_file(int argc, char* argv[], edlin_file_t* file);

bool edlin_edit(edlin_file_t* file); // main edit loop

#endif

#include "edlin_file.h"
#include "edlin_constants.h"
#include "edlin_errors.h"
#include "edlin_types.h"
#include "edlin_kbd.h"
#include "../DOS/dos_memory.h"
#include <string.h>
#include <stdlib.h>

edlin_file_t* edlin_new_file() {
    // 1. allocate a file struct
    edlin_file_t* file = malloc(sizeof(edlin_file_t));
    if (!file) {
        return NULL;
    }
    // 2. allocate line pointers for 75% of DOS free memory
    file->capacity = (dos_memory_available() * 0.75f) / EDLIN_LINE_SIZE;
    file->lines = calloc(file->capacity, sizeof(edlin_line_t*));  // arrray of null line pointers
    if (!file->lines) {
        free(file);
        return NULL;
    }
    // 3. set defaults
    file->filepath = NULL;
    file->raw = false;
    file->size = 0;
    return file;
}

void edlin_free_file(edlin_file_t* file) {
    if(!file) {
        return;
    }
    if (file->lines) {
        for (edlin_size_t i = 0; i < file->size; i++) {
            free(file->lines[i]);
        }
        free(file->lines);
    }
    free(file);
}

edlin_line_t* edlin_new_line() {
     edlin_line_t* line = calloc(1, EDLIN_LINE_SIZE);
     if(!line) {
         edlin_panic(EDLIN_ERR_ALLOC, "new line failed!");
     }
     return line;
}

// Read a line from input stream into buffer
bool edlin_read_line(edlin_line_t* line, FILE* istream) {
    if (!fgets((char*)line, EDLIN_LINE_SIZE, istream)) {
        if (feof(istream)) {
            return false;  // Graceful EOF indication
        } else {
            edlin_panic(EDLIN_ERR_STREAM, "read line failed!");
            return false;
        }
    }
    return true;
}

bool edlin_load_file(edlin_file_t* file) {
    if (!file) {
        edlin_panic(EDLIN_ERR_NULL, "Null pointer in load file");
        return false;
    }
    // select binary or text file open
    FILE* f = fopen((const char*)file->filepath, file->raw ? "rb" : "r");
    if (!f) {
        file->size = 0;
        return true;    // create file when save
    }
    file->size = 0;
    edlin_line_t* line;

    while (true) {
        if (file->size == file->capacity) {
            fclose(f);
            return false;
        }
        line = edlin_new_line();
        if (!line) {
            fclose(f);
            return false;
        }
        if (!edlin_read_line(line, f)) {
            free(line);
            break;
        }
        file->lines[file->size++] = line;
    }

    fclose(f);
    return true;
}

void edlin_print_file(edlin_file_t* file) {
    for(edlin_size_t i = 0; i < file->size; ++i) {
        printf("%s", *file->lines[i]);
        if (
            (i + 1) % EDLIN_PAGE_SIZE == 0
            && i + 1 < file->size
            && !edlin_kbd_yesno("Continue ")
        ) {
            printf("\n");
            return;
        }
    }
}


/*
void edlin_trim_line(edlin_line_t* line) {
    if (line == NULL) return;
    char* p = *line;
    // Trim newline and anything after it
    size_t len = strcspn(p, "\n");
    p[len] = '\0';
    // Trim trailing whitespace
    while (len > 0 && isspace((unsigned char)p[len - 1])) {
        p[--len] = '\0';
    }
}
 */

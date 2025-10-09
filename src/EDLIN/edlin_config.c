#include "edlin_config.h"
#include "edlin_errors.h"
#include "edlin_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static const char EDLIN_INTRO[] = " \
\nEDLIN 0.03, copyright (c) 2025 Jeremy Thornton\n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
It is free software, and you are welcome to redistribute it\n\
under the terms of the MIT License.\n\n\
";

static const char EDLIN_USAGE[] = " usage: EDLIN [path] <file name> [/B]";

static const char EDLIN_MSG_FILENAME[] = "File name must be specified";

void edlin_intro() {
    printf("%s", EDLIN_INTRO);
}

void edlin_usage() {
    printf("%s", EDLIN_USAGE);
}

bool edlin_config(int argc, char* argv[], edlin_file_t* file) {
    if(argc == 1) {
        edlin_panic(EDLIN_ERR_MISSING_ARG, EDLIN_MSG_FILENAME);
        return false;
    }
    for(int i = 1; i < argc; ++i) {
        if (argv[i][0] != '/') {
            if (file->filepath != NULL) {
                edlin_panic(EDLIN_ERR_MULTIPLE_FILENAMES,argv[i]);
                return false;
            }
            file->filepath = argv[i];
            continue;
        }
        switch (toupper(argv[i][1])) {
        case 'B':
            file->raw = true;
            break;
        default:
            edlin_panic(EDLIN_ERR_UKNOWN_OPT,argv[i]);
            return false;
        }
    }
    if(!file->filepath) {
        edlin_panic(EDLIN_ERR_MISSING_ARG, EDLIN_MSG_FILENAME);
        return false;
    }
    if(!edlin_load_file(file)) {
        return false;
    }
    printf("%s: %u lines read\n", file->filepath, file->size);
    return true;
}

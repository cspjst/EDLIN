#include "edlin_config.h"
#include "edlin_errors.h"
#include "edlin_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

bool edlin_config(int argc, char* argv[], edlin_file_t* file) {
    if(argc == 1) {
        edlin_panic(EDLIN_ERR_SPECIFY_FILE);
        return false;
    }
    for(int i = 1; i < argc; ++i) {
        if (argv[i][0] != '/') {
            if (file->filepath != NULL) {
                edlin_panic(EDLIN_ERR_INVALID_ARG);
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
            edlin_panic(EDLIN_ERR_INVALID_ARG);
            return false;
        }
    }
    if(!edlin_load_file(file)) {
        return false;
    }
    if(file->size) printf("End of input file\n");
    else printf("New file\n");
    return true;
}

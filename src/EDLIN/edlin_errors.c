#include "edlin_errors.h"
#include <stdio.h>

// EDLIN DOS error messages
const char* const EDLIN_ERROR_MESSAGES[] = {
    "Cannot edit .BAK file - rename file",      // EDLIN_ERR_RENAME_BAK
    "No room in directory for file",            // EDLIN_ERR_NO_ROOM
    "Entry error",                              // EDLIN_ERR_ENTRY
    "Line too long",                            // EDLIN_ERR_TOO_LONG
    "Disk Full - write not completed",          // EDLIN_ERR_DISK_FULL
    "Incorrect DOS version",                    // EDLIN_ERR_WRONG_DOS
    "Invalid drive name or file",               // EDLIN_ERR_INVALID_PATH
    "File name must be specified",              // EDLIN_ERR_SPECIFY_FILE
    "Insufficient memory",                      // EDLIN_ERR_INSUFF_MEMORY
    "File not found",                           // EDLIN_ERR_NOT_FOUND
    "Must specify destination number",          // EDLIN_ERR_SPECIFY_DEST
    "Not enough room to merge the entire file", // EDLIN_ERR_FAIL_MERGE
    "File creation error",                      // EDLIN_ERR_FAIL_CREATE
    "Invalid Parameter"                         // EDLIN_ERR_INVALID_ARG
};

void* edlin_panic(edlin_err_t e) {
  printf("%s\n",
      EDLIN_ERROR_MESSAGES[e]
  );
  return NULL;
}

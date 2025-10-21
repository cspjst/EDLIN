
#include "str_types.h"

static const str_size_t str_errno;

static const str_fixed_t ERROR_MESSAGES[] = {
    {"Success", 7, 0},
    {"Null pointer", 12, 0},
    {"Buffer overflow", 15, 0},
    {"Invalid number base", 19, 0},
    {"I/O error", 9, 0},
    {"Empty string", 12, 0},
    {"Invalid pointer", 15, 0}
};

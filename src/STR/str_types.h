#ifndef STR_TYPES_H
#define STR_TYPES_H

#include "str_constants.h"
#include <stdint.h>

typedef uint8_t str_size_t;

typedef struct {
    char text[STR_FIXED_SIZE];
    str_size_t size;
    uint8_t flags;
} str_fixed_t;

typedef enum {
    STDIN = 0,
    STDOUT,
    STDERR,
    PRN
} str_devices_t;

#endif

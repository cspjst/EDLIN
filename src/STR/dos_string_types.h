#ifndef STR_TYPES_H
#define STR_TYPES_H

#include "dos_string_constants.h"
#include <stdint.h>

typedef uint8_t str_size_t;

#pragma pack(1)
typedef struct {
    char text[STR_FIXED_SIZE];
    str_size_t size;
    uint8_t flags;
} str_fixed_t;
#pragma pack()

#endif

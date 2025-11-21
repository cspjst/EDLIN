#ifndef STR_FIXED_H
#define STR_FIXED_H

#include <stdint.h>
#include <stdbool.h>

// constants
#define STR_FIXED_SIZE  254
#define STR_UNDEFINED       0

// flags bits 2..7 are availble to user
#define STR_FLAG_ALLOCATED  0
#define STR_FLAG_OVERSIZED  1

// typedefs
typedef uint8_t str_size_t;

// structs
#pragma pack(1)
typedef struct {
    char text[STR_FIXED_SIZE];
    str_size_t size;
    uint8_t flags;
} str_fixed_t;
#pragma pack()

// functions
void str_flag_set(str_fixed_t* str, uint8_t flag_bit);
void str_flag_clr(str_fixed_t* str, uint8_t flag_bit);
bool str_flag_test(const str_fixed_t* str, uint8_t flag_bit);

#endif

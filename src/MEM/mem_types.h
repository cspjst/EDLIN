#ifndef MEM_TYPES_H
#define MEM_TYPES_H

#include <stdint.h>

typedef uint16_t    mem_size_paragraphs_t;
typedef uint32_t	mem_size_bytes_t;
typedef int32_t		mem_diff_bytes_t;

typedef struct {
    uint16_t offset;
    uint16_t segment;       // reverse order as Intel is little-endian
} mem_segoff_t;

typedef union {
    char* ptr;
    uint32_t memloc;
    mem_segoff_t segoff;
    uint16_t words[2];
    uint8_t bytes[4];
} mem_address_t;

#endif

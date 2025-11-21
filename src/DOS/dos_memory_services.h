#ifndef DOS_MEMORY_SERVICES_H
#define DOS_MEMORY_SERVICES_H

#include <stdint.h>

#define DOS_PARAGRAPH_SIZE  16UL


#pragma pack(1)
typedef struct {
    uint16_t offset;
    uint16_t segment;       // reverse order as Intel is little-endian
} dos_segoff_t;
#pragma pack()

typedef union {
    void* ptr;
    uint32_t memloc;
    mem_segoff_t segoff;
    uint16_t words[2];
    uint8_t bytes[4];
} dos_address_t;

uint16_t dos_get_free_memory_paragraphs();

#endif

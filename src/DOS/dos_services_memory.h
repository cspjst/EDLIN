#ifndef DOS_MEMORY_H
#define DOS_MEMORY_H

#include <stdint.h>

#define DOS_SERVICE 0x21
#define DOS_ALLOCATE_MEMORY_BLOCKS  48h
#define DOS_ERROR 0FFFFh
#define DOS_INSUFFICIENT_MEMORY 8
#define DOS_PARAGRAPH_SIZE 16L
#define DOS_MCB_OVERHEAD DOS_PARAGRAPH_SIZE

uint32_t dos_memory_available();

#endif

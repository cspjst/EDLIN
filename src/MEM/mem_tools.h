#ifndef MEMTOOLS_H
#define MEMTOOLS_H

#include "mem_constants.h"
#include "mem_types.h"
#include "../BIOS/bios_memory_services.h"
#include <stdint.h>

mem_size_paragraphs_t mem_get_free_paragraphs();

inline mem_size_bytes_t mem_get_startup_bytes() {
    return (mem_size_bytes_t)bios_get_startup_memory_kb() * MEM_1K_SIZE;
}

inline mem_size_bytes_t mem_get_free_bytes() {
    return (mem_size_bytes_t)mem_get_free_paragraphs() * MEM_PARAGRAPH_SIZE;
}



#endif

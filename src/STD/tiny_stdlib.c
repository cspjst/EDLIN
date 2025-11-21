#include "tiny_stdlib.h"
#include "tiny_assert.h"
#include "../DOS/dos_memory_services.h"

void* malloc(size_t size) {
    dos_address_t addr = {0};
    size = (uint16_t)((size + 15) >> 4); // convert to paragraphs (roundup) 
    addr.segoff.segment = dos_allocate_memory_blocks(size);
    return addr.ptr;
}

void free(void* p) {
    dos_address_t addr = {0};
    addr.ptr = p;
    assert(dos_free_allocated_memory_blocks(addr.segoff.segment) == 0);
}

void* calloc(size_t n, size_t size) {

}

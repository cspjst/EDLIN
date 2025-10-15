#include "strtools.h"

uint16_t cstr_length(const char* p) {
    uint16_t n = 0;
    while (*p++) n++;
    return n;
}

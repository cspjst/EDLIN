#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <stdint.h>

uint16_t cstr_length(const char* p);

char* cstr_int_to_alpha(int value, char* buffer, int base);

#endif

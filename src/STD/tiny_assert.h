#ifndef TINY_ASSERT_H
#define TINY_ASSERT_H

#include "tiny_stdlib.h"
#include "tiny_stdio.h"

#ifdef NDEBUG
    #define assert(expr) ((void)0)
#else
#define assert(condition) \
    ((condition) \
    ? (void)0 \
    : (printf("Assertion failed: %s, file %s, line %d\n", \
             #condition, __FILE__, __LINE__), \
        exit(1)))
#endif

#endif

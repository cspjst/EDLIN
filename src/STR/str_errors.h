#ifndef STR_ERRORS_H
#define STR_ERRORS_H

typedef enum {
    STR_SUCCESS = 0,
    STR_ERROR_NULL,
    STR_ERROR_OVERFLOW,
    STR_ERROR_INVALID_BASE,
    STR_ERROR_IO,
    STR_ERROR_EMPTY,
    STR_ERROR_INVALID_PTR
} str_error_t;

static const str_size_t str_errno;

#endif

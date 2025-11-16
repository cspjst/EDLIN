#include "str_fixed.h"
#include <stddef.h>

void str_flag_set(str_fixed_t* str, uint8_t flag_bit) {
    if (str == NULL || flag_bit > 7) return;
    str->flags |= (1 << flag_bit);
}

void str_flag_clr(str_fixed_t* str, uint8_t flag_bit) {
    if (str == NULL || flag_bit > 7) return;
    str->flags &= ~(1 << flag_bit);
}

bool str_flag_test(const str_fixed_t* str, uint8_t flag_bit) {
    if (str == NULL || flag_bit > 7) return 0; // Validate input
    return (str->flags & (1 << flag_bit)) ? 1 : 0;
}

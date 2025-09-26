#ifndef BIOS_KEYBOARD_TYPES_H
#define BIOS_KEYBOARD_TYPES_H

#include <stdint.h>

typedef uint8_t bios_keybd_info_t;

#pragma pack(1)
typedef struct {
    uint8_t ascii;
    uint8_t scan;
} bios_key_parts_t;
#pragma pack()

typedef union {
    uint16_t combined;
    bios_key_parts_t parts;
} bios_key_t;

#pragma pack(1)
typedef struct {
    bios_key_t key;
    uint8_t is_pressed;
} bios_key_event_t;
#pragma pack()

#endif

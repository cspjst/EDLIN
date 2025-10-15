#include "edlin_yesno.h"
#include "../BIOS/bios_keyboard_services.h"
#include "../BIOS/bios_keyboard_scan_codes.h"
#include <stdio.h>

bool edlin_yesno(const char* question) {
    printf("%s(Y/N)?", question);
    fflush(stdout);
    bios_key_t key;
    bios_wait_for_keystroke_and_read(&key);
    if (key.parts.scan !=  SCAN_Y) printf("\n");
    return key.parts.scan ==  SCAN_Y;
}

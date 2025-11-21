#include "dos_memory_services.h" 
#include "../DOS/dos_error_types.h"
#include "../DOS/dos_services_constants.h"

/**
 * Report DOS user available low memory
 * Abuses the DOS dos_allocate_memory_blocks function by forcing an error.
 * By setting BX=FFFFh before calling, this function can be used to find the amount of
 * available memory, which will be returned in BX. (The call will return an error, which can be
 * ignored, since DOS cannot allocate more than 640k of memory.)
 */
uint16_t dos_get_free_memory_paragraphs() {
    uint16_t low_free;
    dos_error_code_t err_code;
    __asm {
        .8086
        pushf
        push    ds

        mov     bx, 0FFFFh                  ; number requested paragraphs
        mov     ah, DOS_ALLOCATE_MEMORY_BLOCKS  ; allocate memory
        int     DOS_SERVICE                 ; 48h service
        mov     err_code, ax                ; CF set, and AX = 08 (Not Enough Mem)
        mov     low_free, bx                ; size in paras of the largest block of low memory available

        pop     ds
        popf
    }
//  assert(err_code == DOS_INSUFFICIENT_MEMORY);
    return low_free;
}

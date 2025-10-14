/**
* @brief INT 21,48 - Allocate Memory
* Allocates a specified number of memory paragraphs.
*
* AH = 48h
* BX = number of memory paragraphs requested
* @note paragraph is a memory unit of size 16 bytes,  relevant primarily (if not exclusively) in x86 real mode
* @url https://en.wikipedia.org/wiki/X86_memory_segmentation
* on return:
* AX = segment address of allocated memory block (MCB + 1para)
*    = error code if CF set  (see DOS ERROR CODES)
* BX = size in paras of the largest block of memory available
*      if CF set, and AX = 08 (Not Enough Mem)
* CF = 0 if successful
*    = 1 if error
*
* Error codes:   7          Memory control blocks destroyed
*                8          Insufficient memory
* @note 1. Call Function 59h for extended error code information (DOS 3.0 and above).
*
* - returns segment address of allocated memory block AX:0000
* - each allocation requires a 16 byte overhead for the MCB
* - returns maximum block size available if error
*
* @note 2. By setting BX=FFFFh before calling, this function can be used to find the amount of
* available memory, which will be returned in BX. (The call will return an error, which can be
* ignored, since DOS cannot allocate more than 640k of memory.)
*
* @see  INT 21,49,  INT 21,4A
*
* @param       number of paragraphs (16 bytes) requested
* @param       segment* pointer to segment variable
* @return      the segment address of the reserved memory or 0 if request failed
*/
#include "dos_services_memory.h"
#include <stdint.h>
#include <assert.h>

uint32_t dos_memory_available() {
    uint16_t paragraphs;
    uint16_t err_code;
    __asm {
        .8086
        pushf
        push    ds

        mov     bx, DOS_ERROR               ; force an error
        mov     ah, DOS_ALLOCATE_MEMORY_BLOCKS  ; allocate memory
        int     DOS_SERVICE                 ; 48h service
        jnc     OK                          ; should fail
        mov     err_code, ax                ; CF set, and AX = 08 (Not Enough Mem)
        mov     paragraphs, bx               ; size in paras of the largest block of memory available
    OK:
        pop     ds
        popf
    }
    assert(err_code == DOS_INSUFFICIENT_MEMORY);

    return paragraphs * DOS_PARAGRAPH_SIZE;
}

#include "memtools.h"
#include "../DOS/dos_services_constants.h"
#include "../DOS/dos_error_types.h"
#include "../DOS/dos_error_messages.h"

/**
 * Report DOS user available low memory
 * Abuses the DOS dos_allocate_memory_blocks function by forcing an error.
 * By setting BX=FFFFh before calling, this function can be used to find the amount of
 * available memory, which will be returned in BX. (The call will return an error, which can be
 * ignored, since DOS cannot allocate more than 640k of memory.)
 */
uint32_t mem_available() {
    return 0;
}

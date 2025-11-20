#include "tiny_stdlib.h"

void exit(int status) {
    __asm {
        .8086
        mov     al, byte ptr [status]  // Exit code in AL
        mov     ah, 4Ch               // DOS terminate process function
        int     21h
        // Program ends here - no return
    }
}

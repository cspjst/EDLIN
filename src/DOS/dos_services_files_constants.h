#ifndef DOS_SERVICES_FILES_CONSTANTS_H
#define DOS_SERVICES_FILES_CONSTANTS_H

#ifdef EOF
    #error "EOF is already defined!"
#endif
#define EOF (-1)

#define DOS_STDIN_HANDLE  0
#define DOS_STDOUT_HANDLE 1
#define DOS_STDERR_HANDLE 2

// Device type and role flags (read-only; set by DOS, but you can test them)
#define DOS_DEV_STDIN           1  // bit 0: standard input device
#define DOS_DEV_STDOUT          2  // bit 1: standard output device
#define DOS_DEV_NUL             4  // bit 2: NUL device
#define DOS_DEV_CLOCK           8  // bit 3: clock device

// Operational mode flags (you can set these via IOCTL 01h)
#define DOS_DEV_TEXT            0
#define DOS_DEV_BINARY          80h    // bit 7: 1 = binary mode, 0 = text (translated) mode
#define DOS_DEV_CHAR            100h   // bit 8: 1 = character device (always set for CON, AUX, etc.)

// Reserved bits (9–15) must be zero; bit 6 is "EOF on input" (read-only, not settable)


#endif

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


#endif

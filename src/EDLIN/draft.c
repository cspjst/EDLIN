#ifndef TINY_ASSERT_H
#define TINY_ASSERT_H

#define assert(condition) \
    do { \
        if (!(condition)) { \
            printf("Assertion failed: %s, file %s, line %d\n", \
                   #condition, __FILE__, __LINE__); \
            /* Maybe call DOS exit function */ \
            for(;;); /* Hang */ \
        } \
    } while(0)

#endif

#include "../DOS/dos_services_files.h"
#include <stddef.h>

#define EOF (-1)

#define SEEK_SET FSEEK_SET
#define SEEK_CUR FSEEK_CUR
#define SEEK_END FSEEK_END

typedef dos_file_handle_t FILE;

#define stdin   ((FILE *)0)
#define stdout  ((FILE *)1)
#define stderr  ((FILE *)2)

int fclose(FILE* stream);

int fgetc(FILE* stream);

FILE* fopen(const char* filename, const char* mode);

int fputc(int c, FILE* stream);

int fputs(const char* str, FILE* stream);

size_t fread(void* ptr, size_t size, size_t count, FILE* stream);

int fseek(FILE* stream, long offset, int origin);

long ftell(FILE* stream);

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

int printf(const char* format, ...);

#define putc(c, stream) fputc(c, stream)

#define putchar(c) fputc(c, stdout)

#define puts(str) (fputs(str, stdout), fputc('\n', stdout))

//=========================================

int fclose(FILE* stream) {
    if (stream == NULL) {
        errno = EINVAL;
        return EOF;
    }

    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;
    dos_error_code_t err = dos_close_file(fh;

    if (err != DOS_SUCCESS) {
        errno = dos_to_errno(err);
        return EOF;
    }

    return 0;  // Success
}

int fgetc(FILE* stream);

FILE* fopen(const char* filename, const char* mode) {
    dos_file_handle_t fh = 0xFFFF;
    dos_error_code_t err = DOS_SUCCESS;
    uint16_t mode_val = *(const uint16_t*)mode;

    switch (mode_val) {
        case 'r':  // 0x0072 - "r" (read only)
            err = dos_open_file(filename, ACCESS_READ_ONLY, &fh;
            break;

        case 0x2B72:  // "r+" (read/write)
            err = dos_open_file(filename, ACCESS_READ_WRITE, &fh;
            break;

        case 'w':  // 0x0077 - "w" (write only)   // For "w" mode, DOS only able create with read/write or read only
        case 0x2B77:  // "w+" (read/write)
            dos_delete_file(filename);  // Truncate by deleting
            err = dos_create_file(filename, CREATE_READ_WRITE, &fh;
            break;

        case 'a':  // 0x0061 - "a" (write only, append)  // For "a" mode, DOS only able create with read/write or read only
        case 0x2B61:  // "a+" (read/write, append)
            err = dos_open_file(filename, ACCESS_READ_WRITE, &fh;
            if (err != DOS_SUCCESS) err = dos_create_file(filename, CREATE_READ_WRITE, &fh;
            if (err == DOS_SUCCESS) dos_move_file_pointer(handle, 0, FSEEK_END, NULL);
            break;

        default:
            err = DOS_INVALID_FUNCTION_NUMBER;
            break;
    }

    if (err != DOS_SUCCESS || fh == 0xFFFF) {
        errno = dos_to_errno(err);
        return NULL;
    }

    return (FILE*)handle; // re-interpret cast uint16_t to FILE*
}

int fputc(int c, FILE* stream) {
    dos_file_handle_t handle = (dos_file_handle_t)(uintptr_t)stream;
    dos_error_code_t dos_err = 0;
    char buffer[2];
    uint16_t bytes_to_write = 1;

    // Prepare buffer - handle \r\n conversion for console
    if (c == '\n' && (stream == stdout || stream == stderr)) {
        buffer[0] = '\r';
        buffer[1] = '\n';
        bytes_to_write = 2;
    } else {
        buffer[0] = c;
    }

    __asm {
        .8086
        pushf
        push    ds
        push    si

        mov     bx, handle
        mov     cx, bytes_to_write
        lea     dx, buffer
        mov     ah, DOS_WRITE_FILE_OR_DEVICE_USING_HANDLE
        int     DOS_SERVICE
        jnc     DONE
        mov     dos_err, ax

DONE:
        pop     si
        pop     ds
        popf
    }

    if (dos_err != 0) {
        errno = dos_to_errno(dos_err);  // Set global errno here
        return EOF;
    }

    return (unsigned char)c;
}


int fputs(const char* str, FILE* stream) {
    while (*str) {
        if (fputc(*str++, stream) == EOF) return EOF;
    }
    return 0;
}

size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
    if (stream == NULL || ptr == NULL) {
        errno = EINVAL;
        return 0;
    }

    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;  // re-interpret cast  FILE* to uint16_t
    uint16_t nbytes = size * count;
    uint16_tread;

    dos_error_code_t err = dos_read_file(handle, nbytes, (char*)ptr, &bytes_read);

    if (err != DOS_SUCCESS) {
        errno = dos_to_errno(err);
        return 0;
    }

    return (bytes_read / size);  // Return number of complete *items* read
}

int fseek(FILE* stream, long offset, int origin) {
    if (stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;
    dos_file_position_t new_pos;

    dos_error_code_t err = dos_move_file_pointer(handle, offset, origin, &new_pos);

    if (err != DOS_SUCCESS) {
        errno = dos_to_errno(err);
        return -1;
    }

    return 0;  // Success
}

long ftell(FILE* stream) {
    if (stream == NULL) {
        errno = EINVAL;
        return -1L;
    }

    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;
    dos_file_position_t pos;

    dos_error_code_t err = dos_move_file_pointer(handle, 0, SEEK_CUR, &pos);

    if (err != DOS_SUCCESS) {
        errno = dos_to_errno(err);
        return -1L;
    }

    return (long)pos;  // Convert DOS 32-bit position to C long
}

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
    if (stream == NULL || ptr == NULL) {
        errno = EINVAL;
        return 0;
    }

    dos_file_handle_t fh = (dos_file_handle_t)(uintptr_t)stream;
    uint16_t nbytes = size * count;
    uint16_t written;

    dos_error_code_t err = dos_write_file(handle, nbytes, (const char*)ptr, &written);

    if (err != DOS_SUCCESS) {
        errno = dos_to_errno(err);
        return 0;
    }

    return (written / size); // Return number of complete *items* written
}

int printf(const char* format, ...);

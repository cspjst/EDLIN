#include "iotools.h"
#include <stddef.h>

int fputc(int c, FILE* stream) {
    if (!stream) return EOF;
    char byte = (char)(c & 0xFF);
    // Translate LF to CR for DOS binary-mode output
    if (byte == '\n') {
        fputc('\r', stream);
    }
    int16_t result = dos_write_file(stream->handle, &byte, 1);
    if (result == -1) {
        stream->error = 0;
        return EOF;
    }
    return (unsigned char)(c & 0xFF);
}

int fputs(const char* s, FILE* stream) {
    if (!stream || !s) return EOF;
    uint16_t len = cstr_length(s);
    if (len == 0) return 0;
    for (uint16_t i = 0; i < len; i++) {
        if (fputc(s[i], stream) == EOF) {
            return EOF;
        }
    }
    return (int)len;
}

int puts(const char *s) {
    int len = fputs(s, stdout);
    if(len != EOF) {
        fputc('\n', stdout);
        len++;
    }
    return len;
}

int fgetc(FILE* stream) {
    if (!stream) return EOF;
    stream->error = 0;
    char byte;
    int16_t result = dos_read_file(stream->handle, &byte, 1);
    if (result == -1) {
        stream->error = 0;
        return EOF;
    }
    if (result == 0) {
        stream->eof = 0;
        return EOF;
    }
    // Translate CR to LF for C compatibility
    if (byte == '\r') {
        return '\n';
    }
    return (unsigned char)byte;
}

char* fgets(char* s, int n, FILE* stream) {
    if (!s || !stream || n <= 0) return NULL;
    s[0] = '\0';
    int i = 0;
    for (; i < n - 1; i++) {
        int c = fgetc(stream);
        if (c == EOF) {
            if (i == 0) return (stream->eof || stream->error) ? NULL : s;
            break;
        }
        s[i] = (char)c;
        if (c == '\n') {
            // Convert CR to LF for internal consistency (optional but conventional)
            s[i] = '\n';
            i++;
            break;
        }
    }
    s[i] = '\0';
    return s;
}

int setmode(dos_file_handle_t fhandle, dos_stream_mode_t mode) {
    dos_error_code_t err = dos_set_stream_mode(fhandle, mode);
    return (err == 0) ? (int)mode : -1;
}

int getmode(dos_file_handle_t fhandle) {
    return (int)dos_get_device_info(fhandle);
}

int feof(FILE* stream) {
    if (!stream) return 0;  // or undefined, but safe to return 0
    return stream->eof ? 1 : 0;
}

void clearerr(FILE* stream) {
    if (stream) {
        stream->eof = 0;
        stream->error = 0;
    }
}

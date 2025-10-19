#include "iotools.h"

int tfputc(int c, tFILE* stream) {
    if (!stream) return EOF;

    // Handle newline translation
    if ((char)c == '\n') {
        // Output CR first
        char cr = '\r';
        int16_t result = dos_write_file(stream->handle, &cr, 1);
        if (result != 1) {
            stream->error = 1;
            return EOF;
        }
    }

    // Output the character (or LF after CR)
    char byte = (char)(c & 0xFF);
    int16_t result = dos_write_file(stream->handle, &byte, 1);
    if (result != 1) {
        stream->error = 1;
        return EOF;
    }

    return (unsigned char)c;
}

int tfputs(const char* s, tFILE* stream) {
    if (!stream || !s) return EOF;
    uint16_t len = cstr_length(s);
    if (len == 0) return 0;
    for (uint16_t i = 0; i < len; i++) {
        if (tfputc(s[i], stream) == EOF) {
            return EOF;
        }
    }
    return (int)len;
}

int tputs(const char *s) {
    int len = tfputs(s, tstdout);
    if(len != EOF) {
        tfputc('\n', tstdout);
        len++;
    }
    return len;
}

int tfgetc(tFILE* stream) {
    if (!stream || stream->eof || stream->error) return EOF;

    char byte;
    int16_t result = dos_read_file(stream->handle, &byte, 1);

    if (result == -1) {
        stream->error = 1;
        return EOF;
    }

    if (result == 0) {
        stream->eof = 1;
        return EOF;
    }

    // Return raw byte exactly as read - NO TRANSLATION
    // This preserves CTRL-Z (0x1A) and all other control characters
    return (unsigned char)byte;
}

char* tfgets(char* s, int n, tFILE* stream) {
    if (!s || !stream || n <= 0) return NULL;
    s[0] = '\0';
    int i = 0;
    for (; i < n - 1; i++) {
        int c = tfgetc(stream);
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

int tfeof(tFILE* stream) {
    if (!stream) return 0;  // or undefined, but safe to return 0
    return stream->eof ? 1 : 0;
}

void tclearerr(tFILE* stream) {
    if (stream) {
        stream->eof = 0;
        stream->error = 0;
    }
}

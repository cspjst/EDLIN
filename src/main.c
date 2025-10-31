#include "EDLIN/edlin_document.h"
#include "EDLIN/edlin_load_buffer.h"
#include "MEM/mem_arena.h"
#include "MEM/mem_tools.h"
#include "STR/dos_string.h"
#include "STR/dos_string_types.h"
#include <assert.h>

int main() {
    str_fixed_t file_path;
    str_in_prompt(cstr("Enter file name: "), &file_path);
    str_out(as_dec(mem_get_free_bytes()), CRLF);
    mem_arena_t* arena = mem_new_arena(mem_get_free_paragraphs());
    str_out(as_dec(mem_get_free_bytes()), CRLF);

    //edlin_document_t* doc = edlin_new_document(arena, &file_path);

    edlin_load_buffer_t* buf = edlin_new_load_buffer(
        file_path.text,
        mem_arena_alloc(arena, 1024),
        1024
    );
    assert(buf);
    str_out(as_dec(sizeof(edlin_load_buffer_t)), CRLF);
    str_out(as_dec(buf->capacity), CRLF);

    mem_free_arena(arena);
    str_out(as_dec(mem_get_free_bytes()), CRLF);
}

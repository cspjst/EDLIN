#include "EDLIN/edlin_document.h"
#include "MEM/mem_arena.h"
#include "MEM/mem_tools.h"

int main() {
    str_out(as_dec(mem_get_free_bytes()), CRLF);
    mem_arena_t* arena = mem_new_arena(mem_get_free_paragraphs());
    str_out(as_dec(mem_get_free_bytes()), CRLF);

    edlin_document_t* doc = edlin_new_document(arena);

    mem_free_arena(arena);
    str_out(as_dec(mem_get_free_bytes()), CRLF);
}

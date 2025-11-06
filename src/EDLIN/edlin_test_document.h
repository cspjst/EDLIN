#ifndef EDLIN_TEST_DOCUMENT_H
#define EDLIN_TEST_DOCUMENT_H

#include "../MEM/mem_arena.h"
#include "../MEM/mem_tools.h"
#include "../STR/dos_string.h"
#include "edlin_document.h"
#include <assert.h>
#include <stdio.h>

void test_document() {
    mem_arena_t arena = mem_new_arena(mem_get_free_paragraphs());
    prtinf("free mem = %li", arena->free_size);
    edlin_document_t* doc = edlin_new_document(arena, str_cstr("TEST.TXT"));
    assert(doc);
    printf("doc pool = %p", doc->pool);
    printf("doc seq  = %p", doc->seq);
    printf("doc fbuf = %p", doc->fbuffer);
    printf("doc curr = %i", doc->curr_line);
    printf("doc bin  = %i", doc->is_binary);
    printf("doc save = %i", doc->is_saved);
}

#endif

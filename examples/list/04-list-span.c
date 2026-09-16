#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COLLECTIONS_IMPORT_LIST
#include "../../collections.h"

int main() {
    // Array constructor for list
    List(int) numbers = list_new((int[]){0, 1, 2, 3, 4, 5, 6, 7, 8});

    Span(int) middle = span(&numbers);
    span_slice_range(&middle, 3, 6);

    Span(int) middle2 = span(&numbers);
    span_chop(&middle2, 3);
    span_chop_end(&middle2, 3);

    List(int) allocated_middle = list_dup(&middle);

    printf("middle            = "); span_dbg(&middle, "%d");           printf(" @ %p\n", middle.data);
    printf("middle2           = "); span_dbg(&middle2, "%d");          printf(" @ %p\n", middle2.data);
    printf("allocated_middle  = "); list_dbg(&allocated_middle, "%d"); printf(" @ %p\n", allocated_middle.data);

    return 0;
}

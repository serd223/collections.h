/*
 * 01-list : Example showcasing basic usage of the List module
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h> // IWYU pragma: keep

#define COLLECTIONS_IMPORT_LIST
#include "../../collections.h"

// This automatically `typedef`s a list type called `List(int)`
// Most primitives have predefined List(...) style types.
// (Can be disabled with COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES)
// TYPEDEF_NAMED_LIST(int);

// If you still want to choose the type name but want the
// definition to be shorter
TYPEDEF_LIST(int, Numbers);

// If you want to create your own types yourself
typedef struct {
    LIST_FIELDS(int);
    int your_field;
} Values;

int main(void) {
    // All three are equivalent while using `list_*` macros.
    Values list = {0};
    // Numbers list = {0};
    // List(int) list = {0};

    list_append(&list, 1);
    list_append(&list, 2);
    list_append(&list, 3);
    list_append(&list, 4);

    printf("pop result = %d\n", list_pop(&list));

    list_dbg(&list, "%d", LIST_FMT_ARG);
    return 0;
}

/*
 * 01-list : Example showcasing basic usage of the List module
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define COLLECTIONS_IMPORT_LIST
#include "../../collections.h"

int main(void) {
    List(int) list = {0};

    list_append(&list, 1);
    list_append(&list, 2);
    list_append(&list, 3);
    list_append(&list, 4);

    printf("pop result = %d\n", list_pop(&list));

    list_dbgn(&list, "%d");
    return 0;
}

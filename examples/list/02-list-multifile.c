/*
 * 02-list-multifile : Example showcasing encapsulation while using the List module
*/

#include <stdio.h> // IWYU pragma: keep
#include <stdlib.h> // IWYU pragma: keep

// As headers only import the module, if you wish to use
// implementation dependent functionality (like non-macro functions)
// you have to also import the module implementation
#define COLLECTIONS_IMPORT_LIST_IMPLEMENTATION

// Implicitly 'import's list
#include "02-list-multifile.h"

int main(void) {
    Weights ws = {0};
    list_append(&ws, 10.);
    list_append(&ws, 30.5);
    list_append(&ws, 40.13213);

    // Use of custom format specifier
    list_dbg(&ws, "%.2f", LIST_FMT_ARG);
    return 0;
}

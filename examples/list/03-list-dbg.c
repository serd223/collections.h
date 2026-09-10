/*
 * 03-list-dbg : Example showcasing advanced usage of `list_dbg` in the List module
*/

#include <stdio.h>
#include <stdlib.h>

#define COLLECTIONS_IMPORT_LIST
#include "../../collections.h"

// Typical String_View type
typedef struct {
    const char* data;
    int len;
} String_View;

// Special format and format argument specifiers for String_View
#define SV_FMT "\"%.*s\""
#define SV_ARG(sv) (sv).len, (sv).data

int main(void) {
    List(String_View) views = {0};
    const char* message = "Hello, World!";
    list_append(&views, ((String_View) {
        .data = message,
        .len = 5
        // "Hello"
    }));
    list_append(&views, ((String_View) {
        .data = message + 5,
        .len = 2
        // ", "
    }));
    list_append(&views, ((String_View) {
        .data = message + 7,
        .len = 6
        // "World!"
    }));
    list_dbgn_ext(&views, SV_FMT, SV_ARG);
    return 0;
}

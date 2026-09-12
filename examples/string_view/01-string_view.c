/*
 * 01-string_view: Example showcasing basic usage of the StringView module
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define COLLECTIONS_IMPORT_STRING_VIEW
#define COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#include "../../collections.h"

int main() {
    StringView s = sv("  Hello, World \t \n ");
    printf("'"SV_FMT"'\n", SV_ARG(s));

    s = sv_trim(s);
    s = sv_chop_until(s, ",").end;

    printf("'"SV_FMT"'\n", SV_ARG(s));
    return 0;
}

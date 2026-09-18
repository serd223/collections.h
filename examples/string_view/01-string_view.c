/*
 * 01-string_view: Example showcasing basic usage of the StringView module
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define COLLECTIONS_IMPORT_STRING_VIEW
#define COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#include "../../collections.h"

int main() {
    StringView s = sv("  Hello, World \t \n ");
    // sv_lit can also be used when creating views from string literals
    // this macro bypasses strlen and uses sizeof
    // StringView s = sv_lit("  Hello, World \t \n ");
    printf("'"SV_FMT"'\n", SV_ARG(s));

    s = sv_trim(s);
    s = sv_chop_until(s, ",").end;

    printf("'"SV_FMT"'\n", SV_ARG(s));
    printf("sv_eq(\", World\", \", World\")      = %s\n", sv_eq(s, sv_lit(", World")) ? "true" : "false");
    printf("sv_starts_with(\", World\", \", W\") = %s\n", sv_starts_with(s, sv_lit(", W")) ? "true" : "false");
    printf("sv_contains(\", World\", \"orl\")    = %s\n", sv_contains(s, sv_lit("orl")) ? "true" : "false");
    return 0;
}

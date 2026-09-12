/*
 * 02-string_view-parser: Example showcasing an `ls` output parser written using the StringView module
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define COLLECTIONS_IMPORT_STRING_VIEW
#define COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#include "../../collections.h"

const char* OUTPUT =
"-rw-r--r--@  1 serd223  staff    27B Sep 10 14:44 .gitignore\n"
"-rw-r--r--@  1 serd223  staff    32K Sep 12 18:31 collections.h\n"
"-rw-r--r--@  1 serd223  staff   372B Sep 10 14:44 Doxyfile\n"
"drwxr-xr-x@  5 serd223  staff   160B Sep 12 17:42 examples\n"
"-rw-r--r--@  1 serd223  staff   1.1K Sep 10 14:44 LICENSE-MIT\n"
"-rw-r--r--@  1 serd223  staff   1.1K Sep 12 18:37 Makefile\n"
"-rw-r--r--@  1 serd223  staff   1.6K Sep 12 15:28 README.md\n";

int main() {
    StringView s = sv(OUTPUT);
    while (s.len > 0) {
        StringViewPair pair = sv_chop_untilc(s, '\n');
        StringView line = pair.l;
        s = sv_chop(pair.r, 1); // chop the newline

        pair = sv_split(line, 11);
        StringView perms = pair.left;
        line = sv_trim_start(pair.right).right;

        pair = sv_chop_matches(line, isdigit);
        StringView links = pair.left;
        line = sv_trim_start(pair.right).right;

        pair = sv_chop_unless(line, isspace);
        StringView owner = pair.left;
        line = sv_trim_start(pair.right).right;

        pair = sv_chop_unless(line, isspace);
        StringView group = pair.left;
        line = sv_trim_start(pair.right).right;

        pair = sv_chop_unless(line, isspace);
        StringView size = pair.left;
        line = sv_trim_start(pair.right).right;

        StringView date = line;
        line = sv_chop(sv_chop_untilc(line, ' ').right, 1);
        line = sv_chop(sv_chop_untilc(line, ' ').right, 1);
        line = sv_chop_untilc(line, ' ').right;
        date.len -= line.len;
        line = sv_chop(line, 1); // chop seperator space

        StringView name = line;

        printf("File '"SV_FMT"' Metadata:\n", SV_ARG(name));
        printf(" Permissions: "SV_FMT"\n", SV_ARG(perms));
        printf(" Links: "SV_FMT"\n", SV_ARG(links));
        printf(" Owner: "SV_FMT"\n", SV_ARG(owner));
        printf(" Group: "SV_FMT"\n", SV_ARG(group));
        printf(" Size: "SV_FMT"\n", SV_ARG(size));
        printf(" Modification Date: "SV_FMT"\n", SV_ARG(date));
    }
    return 0;
}

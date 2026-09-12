# collections.h
`collections.h` is a module based & header only collections library for C.

## Modules
Currently, `collections.h` has the following modules:
  * List (COLLECTIONS_IMPORT_LIST)
  * StrMap (COLLECTIONS_IMPORT_STRMAP)
  * StringView (COLLECTIONS_IMPORT_STRING_VIEW)

### List
Implements a generic and easy to use dynamic array/list/vector/whatever your language of choice calls it.

(Truncated from [examples/list/01-list.c](examples/list/01-list.c))
```c
  #include <stdio.h>

  // Also included in the global #define COLLECTIONS_IMPORT
  #define COLLECTIONS_IMPORT_LIST
  #include <collections.h>

  int main(void) {
    List(int) values = {0};
    list_append(&values, 10);
    list_append(&values, 20);
    list_append(&values, 30);
    list_dbgn(&values, "%d");
    // prints "{10, 20, 30}" with a newline
  }
```
For more examples, check out the [List examples folder](examples/list).

### StrMap
Implements a generic and simple HashMap with string keys. Uses linear probing, not very performant but gets the job done.

(Truncated from [examples/strmap/01-strmap.c](examples/strmap/01-strmap.c))
```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  // Also included in the global #define COLLECTIONS_IMPORT and
  // #define COLLECTIONS_IMPORT_IMPLEMENTATION
  #define COLLECTIONS_IMPORT_STRMAP
  #define COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION
  #include <collections.h>

  int main(void) {
      StrMap(float) weights = {0};
      strmap_put(&weights, "a", 1.0);
      strmap_put(&weights, "b", 2.0);
      strmap_put(&weights, "c", 3.0);
      strmap_dbg(&weights, "%f");
      return 0;
  }
```
For more examples, check out the [StrMap examples folder](examples/strmap).

### StringView
Implements a simple StringView type and helper functions.

(Truncated from [examples/string_view/01-string_view.c](examples/string_view/01-string_view.c))
```c
  #include <stdio.h>
  #include <string.h>
  #include <ctype.h>

  // Also included in the global #define COLLECTIONS_IMPORT and
  // #define COLLECTIONS_IMPORT_IMPLEMENTATION
  #define COLLECTIONS_IMPORT_STRING_VIEW
  #define COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
  #include <collections.h>

  int main() {
      StringView s = sv("  Hello, World \t \n ");
      s = sv_trim(s);
      s = sv_chop_until(s, ",").end;
      printf("'"SV_FMT"'\n", SV_ARG(s));
      // Prints ', World'
      return 0;
  }
```
For more examples, check out the [StringView examples folder](examples/string_view).

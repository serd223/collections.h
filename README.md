# collections.h
`collections.h` is a module based & header only collections library for C.

## Modules
Currently, `collections.h` has the following modules:
  * List (COLLECTIONS_IMPORT_LIST)
  * StrMap (COLLECTIONS_IMPORT_STRMAP)

Each module can be 'imported' before including `collections.h` like the following:
```c
#define COLLECTIONS_IMPORT_MODULENAME // like COLLECTIONS_IMPORT_LIST
// #define COLLECTIONS_IMPORT_MODULENAME_IMPLEMENTATION // Includes function implementations, too.
#include <collections.h>
```
You can also pick and choose which implementations to include for which module:
```c
#define COLLECTIONS_IMPORT_SOMEMODULE
#define COLLECTIONS_IMPORT_SOMEMODULE_IMPLEMENTATION
#define COLLECTIONS_IMPORT_OTHERMODULE
#include <collections.h>
// Both the declarations and implementations will be included for SOMEMODULE
// while for OTHERMODULE, only the declarations will be included.
```

The repo contains examples for each module inside the [examples folder](./examples). You can use the provided [Makefile](Makefile) to compile each example. Build artifacts are placed inside a `build` folder at the root of the repository (created if it doesn't exist).

Here is an overview of each module:

### List
Implements a generic and easy to use dynamic array/list/vector/whatever your language of choice calls it.

(Truncated from [examples/list/01-list.c](examples/list/01-list.c))
```c
  #include <stdio.h>

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

(Truncated from [examples/list/01-strmap.c](examples/strmap/01-strmap.c))
```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

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

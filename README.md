# collections.h
`collections.h` is a module based & header only collections library for C.

## Modules
Currently, `collections.h` has the following modules:
  * List (COLLECTIONS_IMPORT_LIST)

Each module can be 'imported' before including `collections.h` like the following:
```c
#define COLLECTIONS_IMPORT_MODULENAME // like COLLECTIONS_IMPORT_LIST
// #define COLLECTIONS_IMPORT_MODULENAME_IMPLEMENTATION // Includes function implementations, too.
#include <collections.h>
```
You can also pick and choose which implementations to include for which module:
```c
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
  #include <collections.h>

  // Different ways to define a List compatible type
  // All are equivalent to the macros in this module
  TYPEDEF_NAMED_LIST(int);
  TYPEDEF_LIST(int, Numbers);
  typedef struct {
      LIST_FIELDS(int);
      int your_field;
  } Values;

  int main(void) {
    List(int) ints = {0};
    Numbers numbers = {0};
    Values values  = {0};
    list_append(&values, 10);
    list_append(&values, 20);
    list_append(&values, 30);
    list_dbg(&values, "%d", LIST_FMT_ARG);
    // prints "{10, 20, 30}" with a newline
  }
```
For more examples, check out the [List examples folder](examples/list)!

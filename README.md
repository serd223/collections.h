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

  #define COLLECTIONS_IMPORT_LIST
  #include <collections.h>

  // Different ways to define a List compatible type:
  // All are equivalent to the macros in this module

  // The List Module provides List type definitions
  // for various primitive types!
  // TYPEDEF_NAMED_LIST(int); // Already defined in collections.h

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

#### Primitive List Types
As mentioned in the example above, the List Module contains predefined List types for various primitives (can be disabled by defining COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES before including `collections.h`).

Here are the supported primitive types (types like `int32_t` that require additional headers are properly handled if they are not defined, you don't need to include all standard definition headers):
  * `char`: `List(char)`
  * `signed char`: `List(signed_char)`
  * `unsigned char`: `List(unsigned_char)`
  * `short`: `List(short)`
  * `signed short`: `List(signed_short)`
  * `unsigned short`: `List(unsigned_short)`
  * `int`: `List(int)`
  * `unsigned int`: `List(unsigned_int)`
  * `short int`: `List(short_int)`
  * `long int`: `List(long_int)`
  * `long`: `List(long)`
  * `unsigned long`: `List(unsigned_long)`
  * `long long`: `List(long_long)`
  * `unsigned long long`: `List(unsigned_long_long)`
  * `float`: `List(float)`
  * `double`: `List(double)`
  * `long double`: `List(long_double)`
  * `void*`: `List(void_ptr)`
  * `char*`: `List(char_ptr)`
  * `signed char*`: `List(signed_char_ptr)`
  * `unsigned char*`: `List(unsigned_char_ptr)`
  * `const char*`: `List(const_char_ptr)`
  * `const signed char*`: `List(const_signed_char_ptr)`
  * `const unsigned char*`: `List(const_unsigned_char_ptr)`
  * `int8_t`: `List(int8_t)`
  * `int16_t`: `List(int16_t)`
  * `int32_t`: `List(int32_t)`
  * `int64_t`: `List(int64_t)`
  * `uint8_t`: `List(uint8_t)`
  * `uint16_t`: `List(uint16_t)`
  * `uint32_t`: `List(uint32_t)`
  * `uint64_t`: `List(uint64_t)`
  * `size_t`: `List(size_t)`
  * `intptr_t`: `List(intptr_t)`
  * `uintptr_t`: `List(uintptr_t)`
  * `ptrdiff_t`: `List(ptrdiff_t)`

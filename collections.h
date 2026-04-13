/*
 * Global Config Macros:
 * - _COLLECTIONS_ASSERT: Customize assert macro globally, can be overwritten per-module. Defaults are managed by modules.
*/

/*
 * List Module
 * Config Macros:
 * - _COLLECTIONS_LIST_ASSERT: Customize assert macro used for this module, defaults to `_COLLECTIONS_ASSERT` if it is available and `assert` if it is not.
 * - COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES: Disables the predefinition of List(...) style types from primitives if defined.
*/
#ifdef COLLECTIONS_IMPORT_LIST

#ifndef ___COLLECTIONS_LIST_HEADER
#define ___COLLECTIONS_LIST_HEADER

#ifndef _COLLECTIONS_LIST_ASSERT
    #ifdef _COLLECTIONS_ASSERT
        #define _COLLECTIONS_LIST_ASSERT _COLLECTIONS_ASSERT
    #else
        #define _COLLECTIONS_LIST_ASSERT assert
    #endif // _COLLECTIONS_ASSERT
#endif // _COLLECTIONS_LIST_ASSERT

#ifdef __SIZE_TYPE__
#define ___COLLECTIONS_LIST_SIZE_T __SIZE_TYPE__
#else // __SIZE_TYPE__
// fallback to size_t
#define ___COLLECTIONS_LIST_SIZE_T size_t
#endif // __SIZE_TYPE__

#define List(ty) ___COLLECTIONS_LIST_TYPE_PREFIX_##ty

#define LIST_FIELDS(ty)\
ty* data;\
___COLLECTIONS_LIST_SIZE_T len;\
___COLLECTIONS_LIST_SIZE_T cap

#define TYPEDEF_LIST(ty, list_ty_name)\
typedef struct {\
    LIST_FIELDS(ty);\
} list_ty_name

#define TYPEDEF_NAMED_LIST(ty) TYPEDEF_LIST(ty, List(ty))

#ifndef COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES
// NOTE: This pattern might actually be useful to end users
#define ___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(ty, ty_lower)\
TYPEDEF_LIST(ty, ___COLLECTIONS_LIST_TYPE_PREFIX_##ty_lower)

TYPEDEF_NAMED_LIST(char);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed char, signed_char);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned char, unsigned_char);

TYPEDEF_NAMED_LIST(short);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed short, signed_short);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned short, unsigned_short);

TYPEDEF_NAMED_LIST(int);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned int, unsigned_int);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(short int, short_int);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long int, long_int);

TYPEDEF_NAMED_LIST(long);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned long, unsigned_long);

___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long long, long_long);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned long long, unsigned_long_long);

TYPEDEF_NAMED_LIST(float);
TYPEDEF_NAMED_LIST(double);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long double, long_double);

___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(void*, void_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(char*, char_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed char*, signed_char_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned char*, unsigned_char_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const char*, const_char_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const signed char*, const_signed_char_ptr);
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const unsigned char*, const_unsigned_char_ptr);

#ifdef __INT8_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT8_TYPE__, int8_t);
#endif // __INT8_TYPE__
#ifdef __INT16_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT16_TYPE__, int16_t);
#endif // __INT16_TYPE__
#ifdef __INT32_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT32_TYPE__, int32_t);
#endif // __INT32_TYPE__
#ifdef __INT64_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT64_TYPE__, int64_t);
#endif // __INT64_TYPE__

#ifdef __UINT8_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT8_TYPE__, uint8_t);
#endif // __UINT8_TYPE__
#ifdef __UINT16_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT16_TYPE__, uint16_t);
#endif // __UINT16_TYPE__
#ifdef __UINT32_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT32_TYPE__, uint32_t);
#endif // __UINT32_TYPE__
#ifdef __UINT64_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT64_TYPE__, uint64_t);
#endif // __UINT64_TYPE__

#ifdef __SIZE_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__SIZE_TYPE__, size_t);
#endif // __SIZE_TYPE__

#ifdef __INTPTR_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INTPTR_TYPE__, intptr_t);
#endif // __INTPTR_TYPE__
#ifdef __UINTPTR_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINTPTR_TYPE__, uintptr_t);
#endif // __UINTPTR_TYPE__
#ifdef __PTRDIFF_TYPE__
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__PTRDIFF_TYPE__, ptrdiff_t);
#endif // __PTRDIFF_TYPE__

#endif // COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES

#define list_append(list, val)\
do {\
    if ((list)->len >= (list)->cap) {\
        (list)->cap = (list)->cap > 0 ? (list)->cap * 2 : 16 * sizeof(*(list)->data);\
        (list)->data = realloc((list)->data, (list)->cap);\
    }\
    (list)->data[(list)->len++] = (val);\
} while(0)

#define list_pop(list) (_COLLECTIONS_LIST_ASSERT((list)->len > 0), (list)->data[--(list)->len])

// NOTE: Should list_dbg print a newline or no?
#define LIST_FMT_ARG(x) x
#define list_dbg(list, fmt, fmt_arg)\
do {\
    if ((list)->len <= 0) break;\
    printf("{");\
    printf(fmt, fmt_arg((list)->data[0]));\
    for (size_t i = 1; i < (list)->len; i++) {\
        printf(", " fmt, fmt_arg((list)->data[i]));\
    }\
    printf("}\n");\
} while(0)

#endif // ___COLLECTIONS_LIST_HEADER

#ifdef COLLECTIONS_IMPORT_LIST_IMPLEMENTATION

#ifndef ___COLLECTIONS_LIST_IMPLEMENTATION
#define ___COLLECTIONS_LIST_IMPLEMENTATION
#endif // ___COLLECTIONS_LIST_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_LIST_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_LIST

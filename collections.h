/** @file collections.h
    The main source file of collections.h.
*/

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

/**
 * @defgroup list List Module
 * @brief List Module Documentation
 *
 * @addtogroup list
 * @{
*/

#ifdef COLLECTIONS_IMPORT_LIST

#ifndef ___COLLECTIONS_LIST_HEADER
#define ___COLLECTIONS_LIST_HEADER

/** @cond */
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
/** @endcond */

/** @brief Refers to a List of type `ty` defined by @link TYPEDEF_NAMED_LIST `TYPEDEF_NAMED_LIST`@endlink */
#define List(ty) ___COLLECTIONS_LIST_TYPE_PREFIX_##ty

/** @brief Helper macro that add necessary list fields of type `ty` to your struct so it can interact with list macros */
#define LIST_FIELDS(ty)\
ty* data;\
___COLLECTIONS_LIST_SIZE_T len;\
___COLLECTIONS_LIST_SIZE_T cap

/** @brief typedefines a List type of type `ty` with the supplied name */
#define TYPEDEF_LIST(ty, list_ty_name)\
typedef struct {\
    LIST_FIELDS(ty);\
} list_ty_name

/** @brief typedefines a List type of type `ty` that can be referred to with the @link List `List`@endlink macro*/
#define TYPEDEF_NAMED_LIST(ty) TYPEDEF_LIST(ty, List(ty))

#ifndef COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES
// NOTE: This pattern might actually be useful to end users
/** @cond */
#define ___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(ty, ty_lower)\
TYPEDEF_LIST(ty, ___COLLECTIONS_LIST_TYPE_PREFIX_##ty_lower)
/** @endcond */

/** @cond */
/** @name Primitive List Types
 * The following types are predefined by collections.h
 * @{
*/

/** @typedef List(char) */
TYPEDEF_NAMED_LIST(char);
/** @typedef List(signed_char) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed char, signed_char);
/** @typedef List(unsigned_char) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned char, unsigned_char);

/** @typedef List(short) */
TYPEDEF_NAMED_LIST(short);
/** @typedef List(signed_short) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed short, signed_short);
/** @typedef List(unsigned_short) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned short, unsigned_short);

/** @typedef List(int) */
TYPEDEF_NAMED_LIST(int);
/** @typedef List(unsigned_int) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned int, unsigned_int);
/** @typedef List(short_int) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(short int, short_int);
/** @typedef List(long_int) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long int, long_int);

/** @typedef List(long) */
TYPEDEF_NAMED_LIST(long);
/** @typedef List(unsigned_long) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned long, unsigned_long);

/** @typedef List(long_long) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long long, long_long);
/** @typedef List(unsigned_long_long) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned long long, unsigned_long_long);

/** @typedef List(float) */
TYPEDEF_NAMED_LIST(float);
/** @typedef List(double) */
TYPEDEF_NAMED_LIST(double);
/** @typedef List(long_double) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(long double, long_double);

/** @typedef List(void_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(void*, void_ptr);
/** @typedef List(char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(char*, char_ptr);
/** @typedef List(signed_char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(signed char*, signed_char_ptr);
/** @typedef List(unsigned_char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(unsigned char*, unsigned_char_ptr);
/** @typedef List(const_char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const char*, const_char_ptr);
/** @typedef List(const_signed_char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const signed char*, const_signed_char_ptr);
/** @typedef List(const_unsigned_char_ptr) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(const unsigned char*, const_unsigned_char_ptr);

#ifdef __INT8_TYPE__
/** @typedef List(int8_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT8_TYPE__, int8_t);
#endif // __INT8_TYPE__
#ifdef __INT16_TYPE__
/** @typedef List(int16_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT16_TYPE__, int16_t);
#endif // __INT16_TYPE__
#ifdef __INT32_TYPE__
/** @typedef List(int32_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT32_TYPE__, int32_t);
#endif // __INT32_TYPE__
#ifdef __INT64_TYPE__
/** @typedef List(int64_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INT64_TYPE__, int64_t);
#endif // __INT64_TYPE__

#ifdef __UINT8_TYPE__
/** @typedef List(uint8_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT8_TYPE__, uint8_t);
#endif // __UINT8_TYPE__
#ifdef __UINT16_TYPE__
/** @typedef List(uint16_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT16_TYPE__, uint16_t);
#endif // __UINT16_TYPE__
#ifdef __UINT32_TYPE__
/** @typedef List(uint32_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT32_TYPE__, uint32_t);
#endif // __UINT32_TYPE__
#ifdef __UINT64_TYPE__
/** @typedef List(uint64_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINT64_TYPE__, uint64_t);
#endif // __UINT64_TYPE__

#ifdef __SIZE_TYPE__
/** @typedef List(size_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__SIZE_TYPE__, size_t);
#endif // __SIZE_TYPE__

#ifdef __INTPTR_TYPE__
/** @typedef List(intptr_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__INTPTR_TYPE__, intptr_t);
#endif // __INTPTR_TYPE__
#ifdef __UINTPTR_TYPE__
/** @typedef List(uintptr_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__UINTPTR_TYPE__, uintptr_t);
#endif // __UINTPTR_TYPE__
#ifdef __PTRDIFF_TYPE__
/** @typedef List(ptrdiff_t) */
___COLLECTIONS_LIST_DEFINE_CUSTOM_PRIMITIVE(__PTRDIFF_TYPE__, ptrdiff_t);
#endif // __PTRDIFF_TYPE__

/** @} */
/** @endcond */

#endif // COLLECTIONS_LIST_DONT_TYPEDEF_PRIMITIVES

/**
 * @brief Appends `val` to the supplied `list`
 * @fn list_append(list, val)
 *
 * @param %list Pointer to a valid List type
 * @param val Value that matches the type of the supplied `list` argument
*/
#define list_append(list, val)\
do {\
    if ((list)->len >= (list)->cap) {\
        (list)->cap = (list)->cap > 0 ? (list)->cap * 2 : 16 * sizeof(*(list)->data);\
        (list)->data = realloc((list)->data, (list)->cap);\
    }\
    (list)->data[(list)->len++] = (val);\
} while(0)

/**
 * @brief Appends `val` to the supplied `list`
 * @fn list_pop(list)
 *
 * @param %list Pointer to a valid List type
 *
 * @return Returns the last element of `list`. Fails bounds check if `list` is empty.
*/
#define list_pop(list) (_COLLECTIONS_LIST_ASSERT((list)->len > 0), (list)->data[--(list)->len])

/**
 * @brief Copies all elements of `src` to `dst`, completely overwriting `dst`
 * @fn list_copy(src, dst)
 *
 * @param src Pointer to a valid List type
 * @param dst Pointer to a valid List type
*/
#define list_copy(src, dst)\
do {\
    (dst)->len = 0;\
    for (___COLLECTIONS_LIST_SIZE_T i = 0; i < (src)->len; ++i) {\
        list_append((dst), (src)->data[i]);\
    }\
} while(0)

/**
 * @brief Helper macro for iterating over Lists
 * @fn list_iter(type, it, list)
 *
 * This macro expands to a for statement that iterates over `list` with an iterator `it` of type `type*`.
 * So for a `list` of `int`s, the invocation would be like `list_iter(int, n, &list) { *n = 5; }`.
 *
 * @param type The type that the `list` List is referring to
 * @param it The name that will be used for the iterator variable
 * @param %list Pointer to a valid List type
*/
#define list_iter(type, it, list) for (type* it = (list)->data; it < (list)->data + (list)->len; ++it)

/**
 * @brief Uses @link list_iter `list_iter`@endlink to apply the supplied `fn` to each element of `list`
 * @fn list_map(type, fn, list)
 *
 * @param type The type that the `list` List is referring to
 * @param fn Pointer to a function of type `type` (*fn)(`type`)
 * @param %list Pointer to a valid List type
*/
#define list_map(type, fn, list) list_iter(type, it, (list)) *it = fn(*it)

/**
 * @brief Removes the element at index `index` from `list` and shifts remaining elements accordingly
 * @fn list_delete(list, index)
 *
 * @param %list Pointer to valid List type
 * @param index Index to be removed
 *
 * @return Returns a pointer to the new `index`th element if applicable. Otherwise, returns a pointer to the last element of the list
*/
#define list_delete(list, index) (_COLLECTIONS_LIST_ASSERT((index) < (list)->len), (index) == (list)->len - 1 ? (list_pop((list)), (list)->data + (list)->len - 1) : (memmove((list)->data + (index), (list)->data + (index)+ 1, (((list)->len--) - (index) - 1) * sizeof(*(list)->data))))

// NOTE: Should list_dbg print a newline or no?
#define LIST_FMT_ARG(x) x

/**
 * @brief Pretty prints the supplied `list` with a newline
 * @fn list_dbg(list, fmt, fmt_arg)
 *
 * @param %list Pointer to vali List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
 * @param fmt_arg Macro that will be applied to each element while printing for even more configuration (like for user defined 'String View' types). LIST_FMT_ARG can be used as a default.
*/
#define list_dbg(list, fmt, fmt_arg)\
do {\
    if ((list)->len <= 0) break;\
    printf("{");\
    printf(fmt, fmt_arg((list)->data[0]));\
    for (___COLLECTIONS_LIST_SIZE_T i = 1; i < (list)->len; i++) {\
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
/** @} */

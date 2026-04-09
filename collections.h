// List Module
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

#define List(ty) ___List_##ty

#define LIST_FIELDS(ty)\
ty* data;\
size_t len;\
size_t cap

#define TYPEDEF_LIST(ty, list_ty_name)\
typedef struct {\
    LIST_FIELDS(ty);\
} list_ty_name

#define TYPEDEF_NAMED_LIST(ty) TYPEDEF_LIST(ty, List(ty))

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

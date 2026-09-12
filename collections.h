/** @file collections.h
    The main source file of collections.h.
*/

#ifndef ___COLLECTIONS_H_DEFAULT_FMT_ARG
#define ___COLLECTIONS_H_DEFAULT_FMT_ARG(x) (x)
#endif // ___COLLECTIONS_H_DEFAULT_FMT_ARG

#ifdef COLLECTIONS_IMPORT
#define COLLECTIONS_IMPORT_LIST
#define COLLECTIONS_IMPORT_STRMAP
#define COLLECTIONS_IMPORT_STRING_VIEW
#endif // COLLECTIONS_IMPORT

#ifdef COLLECTIONS_IMPORT_IMPLEMENTATION
#define COLLECTIONS_IMPORT_LIST_IMPLEMENTATION
#define COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION
#define COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#endif // COLLECTIONS_IMPORT_IMPLEMENTATION

#ifndef _COLLECTIONS_APIDEF
#define _COLLECTIONS_APIDEF
#endif // _COLLECTIONS_APIDEF

#ifndef _COLLECTIONS_SIZE_T

#ifdef __SIZE_TYPE__
#define _COLLECTIONS_SIZE_T __SIZE_TYPE__
#else // __SIZE_TYPE__
// fallback to size_t
#define _COLLECTIONS_SIZE_T size_t
#endif // __SIZE_TYPE__

#endif // _COLLECTIONS_SIZE_T

#ifndef _COLLECTIONS_ASSERT
#define _COLLECTIONS_ASSERT assert
#endif // _COLLECTIONS_ASSERT

#ifndef _COLLECTIONS_REALLOC
#define _COLLECTIONS_REALLOC realloc
#endif // _COLLECTIONS_REALLOC

#ifndef _COLLECTIONS_MALLOC
#define _COLLECTIONS_MALLOC malloc
#endif // _COLLECTIONS_MALLOC

#ifndef _COLLECTIONS_FREE
#define _COLLECTIONS_FREE free
#endif // _COLLECTIONS_FREE

#ifndef _COLLECTIONS_MEMMOVE
#define _COLLECTIONS_MEMMOVE memmove
#endif // _COLLECTIONS_MEMMOVE

#ifndef _COLLECTIONS_MEMCPY
#define _COLLECTIONS_MEMCPY memcpy
#endif // _COLLECTIONS_MEMCPY

#ifndef _COLLECTIONS_STRDUP
#define _COLLECTIONS_STRDUP strdup
#endif // _COLLECTIONS_STRDUP

#ifndef _COLLECTIONS_STRLEN
#define _COLLECTIONS_STRLEN strlen
#endif // _COLLECTIONS_STRLEN

#ifndef _COLLECTIONS_STRCMP
#define _COLLECTIONS_STRCMP strcmp
#endif // _COLLECTIONS_STRCMP

#ifndef _COLLECTIONS_ISSPACE
#define _COLLECTIONS_ISSPACE isspace
#endif // _COLLECTIONS_ISSPACE

#ifndef _COLLECTIONS_FPRINTF
#define _COLLECTIONS_FPRINTF fprintf
#endif // _COLLECTIONS_FPRINTF

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
#ifndef _COLLECTIONS_LIST_APIDEF
#define _COLLECTIONS_LIST_APIDEF _COLLECTIONS_APIDEF
#endif // _COLLECTIONS_LIST_APIDEF

#ifndef _COLLECTIONS_LIST_ASSERT
#define _COLLECTIONS_LIST_ASSERT _COLLECTIONS_ASSERT
#endif // _COLLECTIONS_LIST_ASSERT

#ifndef _COLLECTIONS_LIST_REALLOC
#define _COLLECTIONS_LIST_REALLOC _COLLECTIONS_REALLOC
#endif // _COLLECTIONS_LIST_REALLOC

#ifndef _COLLECTIONS_LIST_MEMMOVE
#define _COLLECTIONS_LIST_MEMMOVE _COLLECTIONS_MEMMOVE
#endif // _COLLECTIONS_LIST_MEMMOVE

#ifndef _COLLECTIONS_LIST_FPRINTF
#define _COLLECTIONS_LIST_FPRINTF _COLLECTIONS_FPRINTF
#endif // _COLLECTIONS_LIST_FPRINTF

#ifndef _COLLECTIONS_SIZE_T
#define _COLLECTIONS_LIST_SIZE_T _COLLECTIONS_SIZE_T
#endif // _COLLECTIONS_SIZE_T
/** @endcond */

/** @brief Helper macro that add necessary list fields of type `ty` to your struct */
#define LIST_FIELDS(ty)\
ty* data;\
_COLLECTIONS_SIZE_T len;\
_COLLECTIONS_SIZE_T cap

/** @brief Refers to an anonymus struct for a List of type `ty` */
#define List(ty)\
struct {\
    LIST_FIELDS(ty);\
}

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
        (list)->data = _COLLECTIONS_LIST_REALLOC((list)->data, (list)->cap);\
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
    for (_COLLECTIONS_SIZE_T i = 0; i < (src)->len; ++i) {\
        list_append((dst), (src)->data[i]);\
    }\
} while(0)

/**
 * @brief Helper macro for iterating over Lists
 * @fn list_iter(list, iteartor)
 *
 * This macro expands to a for statement that iterates over `list` with an iterator `it` of type `type*`.
 * So for a `list` of `int`s, the invocation would be like `list_iter(int, n, &list) { *n = 5; }`.
 *
 * @param %list Pointer to a valid List type
 * @param iterator The name that will be used for the iterator variable
*/
#define list_iter(list, iterator) for (__typeof__((list)->data) it = (list)->data; it < (list)->data + (list)->len; ++it)

/**
 * @brief Removes the element at index `index` from `list` and shifts remaining elements accordingly
 * @fn list_remove(list, index)
 *
 * @param %list Pointer to valid List type
 * @param index Index to be removed
 *
 * @return Returns a pointer to the new `index`th element if applicable. Otherwise, returns a pointer to the last element of the list
*/
#define list_remove(list, index) (_COLLECTIONS_LIST_ASSERT((index) < (list)->len), (index) == (list)->len - 1 ? (list_pop((list)), (list)->data + (list)->len - 1) : (_COLLECTIONS_LIST_MEMMOVE((list)->data + (index), (list)->data + (index)+ 1, (((list)->len--) - (index) - 1) * sizeof(*(list)->data))))

/**
 * @brief Pretty prints the supplied `list` into `file`
 * @fn list_fdbg(file, list, fmt)
 *
 * @param file FILE* to print into
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
*/
#define list_fdbg(file, list, fmt)\
do {\
    list_fdbg_ext((file), (list), fmt, ___COLLECTIONS_H_DEFAULT_FMT_ARG);\
} while(0)

/**
 * @brief Pretty prints the supplied `list` into `file`
 * @fn list_fdbg_ext(file, list, fmt, fmt_arg)
 *
 * @param file FILE* to print into
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
 * @param fmt_arg Macro that will be applied to each element while printing for even more configuration (like for user defined 'String View' types). LIST_FMT_ARG can be used as a default.
*/
#define list_fdbg_ext(file, list, fmt, fmt_arg)\
do {\
    if ((list)->len <= 0) break;\
    _COLLECTIONS_LIST_FPRINTF((file), "{");\
    _COLLECTIONS_LIST_FPRINTF((file), fmt, fmt_arg((list)->data[0]));\
    for (_COLLECTIONS_SIZE_T i = 1; i < (list)->len; i++) {\
        _COLLECTIONS_LIST_FPRINTF((file), ", " fmt, fmt_arg((list)->data[i]));\
    }\
    _COLLECTIONS_LIST_FPRINTF((file), "}");\
} while(0)

/**
 * @brief Pretty prints the supplied `list` with a newline into `file`
 * @fn list_fdbgn(file, list, fmt)
 *
 * @param file FILE* to print into
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
*/
#define list_fdbgn(file, list, fmt)\
do {\
    list_fdbg((file), (list), fmt);\
    _COLLECTIONS_LIST_FPRINTF((file), "\n");\
} while(0)

/**
 * @brief Pretty prints the supplied `list` with a newline into `file`
 * @fn list_fdbgn_ext(file, list, fmt, fmt_arg)
 *
 * @param file FILE* to print into
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
 * @param fmt_arg Macro that will be applied to each element while printing for even more configuration (like for user defined 'String View' types). LIST_FMT_ARG can be used as a default.
*/
#define list_fdbgn_ext(file, list, fmt, fmt_arg)\
do {\
    list_fdbg_ext((file), (list), fmt, fmt_arg);\
    _COLLECTIONS_LIST_FPRINTF((file), "\n");\
} while(0)

/**
 * @brief Pretty prints the supplied `list`
 * @fn list_dbg(list, fmt)
 *
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
*/
#define list_dbg(list, fmt) list_fdbg(stdout, (list), fmt)

/**
 * @brief Pretty prints the supplied `list` with a newline
 * @fn list_dbgn(list, fmt)
 *
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
*/
#define list_dbgn(list, fmt) list_fdbgn(stdout, (list), fmt)

/**
 * @brief Pretty prints the supplied `list`
 * @fn list_dbg_ext(list, fmt, fmt_arg)
 *
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
 * @param fmt_arg Macro that will be applied to each element while printing for even more configuration (like for user defined 'String View' types). LIST_FMT_ARG can be used as a default.
*/
#define list_dbg_ext(list, fmt, fmt_arg) list_fdbg_ext(stdout, (list), fmt, fmt_arg)

/**
 * @brief Pretty prints the supplied `list` with a newline
 * @fn list_dbgn_ext(list, fmt, fmt_arg)
 *
 * @param %list Pointer to valid List type
 * @param fmt Format specifier to be used for each element of `list` (like "%d" for a List of `int`s)
 * @param fmt_arg Macro that will be applied to each element while printing for even more configuration (like for user defined 'String View' types). LIST_FMT_ARG can be used as a default.
*/
#define list_dbgn_ext(list, fmt, fmt_arg) list_fdbgn_ext(stdout, (list), fmt, fmt_arg)

#endif // ___COLLECTIONS_LIST_HEADER

#ifdef COLLECTIONS_IMPORT_LIST_IMPLEMENTATION

#ifndef ___COLLECTIONS_LIST_IMPLEMENTATION
#define ___COLLECTIONS_LIST_IMPLEMENTATION
#endif // ___COLLECTIONS_LIST_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_LIST_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_LIST
/** @} */

#ifdef COLLECTIONS_IMPORT_STRMAP

#ifndef ___COLLECTIONS_STRMAP_HEADER
#define ___COLLECTIONS_STRMAP_HEADER

/** @cond */
#ifndef _COLLECTIONS_STRMAP_APIDEF
#define _COLLECTIONS_STRMAP_APIDEF _COLLECTIONS_APIDEF
#endif // _COLLECTIONS_STRMAP_APIDEF

#ifndef _COLLECTIONS_STRMAP_ASSERT
#define _COLLECTIONS_STRMAP_ASSERT _COLLECTIONS_ASSERT
#endif // _COLLECTIONS_STRMAP_ASSERT

#ifndef _COLLECTIONS_STRMAP_REALLOC
#define _COLLECTIONS_STRMAP_REALLOC _COLLECTIONS_REALLOC
#endif // _COLLECTIONS_STRMAP_REALLOC

#ifndef _COLLECTIONS_STRMAP_FREE
#define _COLLECTIONS_STRMAP_FREE _COLLECTIONS_FREE
#endif // _COLLECTIONS_STRMAP_FREE

#ifndef _COLLECTIONS_STRMAP_MEMCPY
#define _COLLECTIONS_STRMAP_MEMCPY _COLLECTIONS_MEMCPY
#endif // _COLLECTIONS_STRMAP_MEMCPY

#ifndef _COLLECTIONS_STRMAP_STRDUP
#define _COLLECTIONS_STRMAP_STRDUP _COLLECTIONS_STRDUP
#endif // _COLLECTIONS_STRMAP_STRDUP

#ifndef _COLLECTIONS_STRMAP_STRCMP
#define _COLLECTIONS_STRMAP_STRCMP _COLLECTIONS_STRCMP
#endif // _COLLECTIONS_STRMAP_STRCMP

#ifndef _COLLECTIONS_STRMAP_FPRINTF
#define _COLLECTIONS_STRMAP_FPRINTF _COLLECTIONS_FPRINTF
#endif // _COLLECTIONS_STRMAP_FPRINTF

#ifdef _COLLECTIONS_SIZE_T
#define _COLLECTIONS_STRMAP_SIZE_T _COLLECTIONS_SIZE_T
#endif // _COLLECTIONS_SIZE_T
/** @endcond */

#define StrMap(ty)\
struct {\
    struct {\
        char* key;\
        int marker;\
    }* keys;\
    ty* data;\
    _COLLECTIONS_STRMAP_SIZE_T _data_field_size;\
    _COLLECTIONS_STRMAP_SIZE_T _key_field_size;\
    _COLLECTIONS_STRMAP_SIZE_T len;\
    _COLLECTIONS_STRMAP_SIZE_T cap;\
}

_COLLECTIONS_STRMAP_APIDEF void* ___strmap_put(void* map, const char* key, void* data, _COLLECTIONS_STRMAP_SIZE_T data_size);
_COLLECTIONS_STRMAP_APIDEF void* ___strmap_get(void* map, const char* key);
_COLLECTIONS_STRMAP_APIDEF int ___strmap_remove(void* map, const char* key, void* out);

#define strmap_put(map, key, val) do {\
    __typeof__(*(map)->data) v = (val);\
    ___strmap_put((map), (key), &v, sizeof(*(map)->data));\
} while (0);
#define strmap_put_ptr(map, key, val) (__typeof__((map)->data))___strmap_put((map), (key), (val), sizeof(*(val)))
#define strmap_get(map, key) (__typeof__((map)->data))___strmap_get((map), (key))
#define strmap_remove(map, key, out) ___strmap_remove((map), (key), (out))

#define strmap_free(map)\
do {\
    strmap_iter((map), k, v, {\
        (void)v;\
        _COLLECTIONS_STRMAP_FREE(k);\
    });\
    _COLLECTIONS_STRMAP_FREE((map)->keys);\
    _COLLECTIONS_STRMAP_FREE((map)->data);\
} while(0)

#define strmap_fdbg(file, map, fmt_data) strmap_fdbg_ext((file), (map), "\"%s\"", fmt_data, ___COLLECTIONS_H_DEFAULT_FMT_ARG, ___COLLECTIONS_H_DEFAULT_FMT_ARG)

#define strmap_fdbg_ext(file, map, fmt_key, fmt_data, fmt_key_arg, fmt_data_arg)\
do {\
    _COLLECTIONS_STRMAP_FPRINTF((file), "{\n");\
    if ((map)->len <= 0) {\
        _COLLECTIONS_STRMAP_FPRINTF((file), "}\n");\
        break;\
    }\
    _COLLECTIONS_STRMAP_SIZE_T found = 0;\
    for (_COLLECTIONS_STRMAP_SIZE_T i = 0; i < (map)->cap; i++) {\
        if ((map)->keys[i].key != NULL && (map)->keys[i].marker == 1) {\
            found++;\
            _COLLECTIONS_STRMAP_FPRINTF((file), "    "fmt_key": "fmt_data",\n", fmt_key_arg((map)->keys[i].key), fmt_data_arg((map)->data[i]));\
        }\
        if (found >= (map)->len) break;\
    }\
    _COLLECTIONS_STRMAP_FPRINTF((file), "}\n");\
} while(0)

#define strmap_dbg(map, fmt_data) strmap_fdbg(stdout, (map), fmt_data)

#define strmap_dbg_ext(map, fmt_key, fmt_data, fmt_key_arg, fmt_data_arg) strmap_fdbg_ext(stdout, (map), fmt_key, fmt_data, fmt_key_arg, fmt_data_arg)

#define strmap_iter(map, key_iter, val_iter, ...)\
do {\
    if ((map)->len <= 0 || (map)->data == NULL) break;\
    _COLLECTIONS_STRMAP_SIZE_T __collections_h_iter_found = 0;\
    for (_COLLECTIONS_STRMAP_SIZE_T __collections_h_iter_i = 0; __collections_h_iter_i < (map)->cap; __collections_h_iter_i++) {\
        if ((map)->keys[__collections_h_iter_i].key != NULL && (map)->keys[__collections_h_iter_i].marker == 1) {\
            __collections_h_iter_found++;\
            __typeof__((map)->keys[__collections_h_iter_i].key) key_iter = (map)->keys[__collections_h_iter_i].key;\
            __typeof__((map)->data) val_iter= &(map)->data[__collections_h_iter_i];\
            __VA_ARGS__\
        }\
        if (__collections_h_iter_found >= (map)->len) break;\
    }\
} while (0)

#endif // ___COLLECTIONS_STRMAP_HEADER

#ifdef COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION

#ifndef ___COLLECTIONS_STRMAP_IMPLEMENTATION
#define ___COLLECTIONS_STRMAP_IMPLEMENTATION

struct ___Collections_StrMap_Generic  {
    struct {
        void* key;
        int marker;
    }* keys;
    void* data;
    _COLLECTIONS_STRMAP_SIZE_T _data_field_size;
    _COLLECTIONS_STRMAP_SIZE_T _key_field_size;
    _COLLECTIONS_STRMAP_SIZE_T len;
    _COLLECTIONS_STRMAP_SIZE_T cap;
};

// https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
_COLLECTIONS_STRMAP_APIDEF unsigned long ___strmap_djb2(const char *str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;

}

_COLLECTIONS_STRMAP_APIDEF _COLLECTIONS_STRMAP_SIZE_T ___strmap_index(struct ___Collections_StrMap_Generic* map, const char* key) {
    _COLLECTIONS_STRMAP_SIZE_T index = ___strmap_djb2(key) & (map->cap - 1);
    while (index < map->cap) {
        if (map->keys[index].key != NULL && _COLLECTIONS_STRMAP_STRCMP(map->keys[index].key, key) == 0) {
            return index;
        } else if (map->keys[index].marker == 0)  {
            return index;
        }
        index = (index + 1) & (map->cap - 1);
    }
    // TODO: Handle failure gracefully
    return map->cap + 1;
}

_COLLECTIONS_STRMAP_APIDEF void* ___strmap_put(void* map, const char* key, void* data, _COLLECTIONS_STRMAP_SIZE_T data_size) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if ((map_->len + 1) >= map_->cap) {
        if (map_->cap == 0) map_->_data_field_size = data_size;
        map_->cap = map_->cap == 0 ? 16 : map_->cap * 2;
        map_->data = _COLLECTIONS_STRMAP_REALLOC(map_->data, map_->cap * map_->_data_field_size);
        map_->keys = _COLLECTIONS_STRMAP_REALLOC(map_->keys, map_->cap * sizeof(*map_->keys));
    }
    _COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
    if (index > map_->cap) return NULL;
    char* map_data = (char*)map_->data + map_->_data_field_size * index;
    _COLLECTIONS_STRMAP_MEMCPY(map_data, data, map_->_data_field_size);
    map_->keys[index].key = _COLLECTIONS_STRMAP_STRDUP(key);
    map_->keys[index].marker = 1;
    map_->len++;

    return map_data;
}

_COLLECTIONS_STRMAP_APIDEF void* ___strmap_get(void* map, const char* key) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if (map_->cap == 0 || map_->len == 0 || map_->data == NULL) return NULL;
    _COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
    if (index >= map_->cap) return NULL;
    if (map_->keys[index].marker != 1) return NULL;
    char* map_data = (char*)map_->data + map_->_data_field_size * index;

    return map_data;
}

_COLLECTIONS_STRMAP_APIDEF int ___strmap_remove(void* map, const char* key, void* out) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if (map_->cap == 0 || map_->len == 0 || map_->data == NULL) return 0;
    _COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
    if (index >= map_->cap) return 0;
    map_->keys[index].marker = 0;
    map_->len--;
    if (out != NULL) {
        char* map_data = (char*)map_->data + map_->_data_field_size * index;
        _COLLECTIONS_STRMAP_MEMCPY(out, map_data, map_->_data_field_size);

    }
    return 1;
}


#endif // ___COLLECTIONS_STRMAP_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION

#endif // COLLECTIONS_IMPORT_STRMAP

#ifdef COLLECTIONS_IMPORT_STRING_VIEW
#ifndef ___COLLECTIONS_STRING_VIEW_HEADER
#define ___COLLECTIONS_STRING_VIEW_HEADER

#ifndef _COLLECTIONS_STRING_VIEW_APIDEF
#define _COLLECTIONS_STRING_VIEW_APIDEF _COLLECTIONS_APIDEF
#endif // _COLLECTIONS_STRING_VIEW_APIDEF

#ifndef _COLLECTIONS_STRING_VIEW_SIZE_T
#define _COLLECTIONS_STRING_VIEW_SIZE_T _COLLECTIONS_SIZE_T
#endif // _COLLECTIONS_STRING_VIEW_SIZE_T

#ifndef _COLLECTIONS_STRING_VIEW_ASSERT
#define _COLLECTIONS_STRING_VIEW_ASSERT _COLLECTIONS_ASSERT
#endif // _COLLECTIONS_STRING_VIEW_ASSERT

#ifndef _COLLECTIONS_STRING_VIEW_STRLEN
#define _COLLECTIONS_STRING_VIEW_STRLEN _COLLECTIONS_STRLEN
#endif // _COLLECTIONS_STRING_VIEW_STRLEN

#ifndef _COLLECTIONS_STRING_VIEW_MEMCPY
#define _COLLECTIONS_STRING_VIEW_MEMCPY _COLLECTIONS_MEMCPY
#endif // _COLLECTIONS_STRING_VIEW_MEMCPY

#ifndef _COLLECTIONS_STRING_VIEW_MALLOC
#define _COLLECTIONS_STRING_VIEW_MALLOC _COLLECTIONS_MALLOC
#endif // _COLLECTIONS_STRING_VIEW_MALLOC

#ifndef _COLLECTIONS_STRING_VIEW_ISSPACE
#define _COLLECTIONS_STRING_VIEW_ISSPACE _COLLECTIONS_ISSPACE
#endif // _COLLECTIONS_STRING_VIEW_ISSPACE

typedef struct {
    const char* data;
    _COLLECTIONS_STRING_VIEW_SIZE_T len;
} StringView;

typedef struct {
    union {
        struct {
            union {
                StringView start;
                StringView left;
                StringView l;
            };
            union {
                StringView end;
                StringView right;
                StringView r;
            };
        };
        StringView v[2];
    };
} StringViewPair;

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int)(sv).len, (sv).data

#define sv(cstr)\
(StringView) {\
    .data = (cstr),\
    .len = _COLLECTIONS_STRING_VIEW_STRLEN((cstr)),\
}

#define sv_copy_cstr(sv, dst)\
(_COLLECTIONS_STRING_VIEW_ASSERT((dst) != NULL), _COLLECTIONS_STRING_VIEW_MEMCPY((dst), (sv).data, (sv).len), (dst)[(sv).len] = 0)

#define sv_alloc_cstr(sv) sv_copy_cstr((sv), _COLLECTIONS_STRING_VIEW_MALLOC(((sv).len + 1) * sizeof(char)));

#define sv_slice(sv, start, len)\
(_COLLECTIONS_STRING_VIEW_ASSERT(((len) + (start)) <= (sv).len), (StringView) {\
    .data = (sv).data + (start),\
    .len = (len),\
})

// [start, end)
#define sv_slice_range(sv, start, end)\
(_COLLECTIONS_STRING_VIEW_ASSERT((end) >= (start)), _COLLECTIONS_STRING_VIEW_ASSERT(((end) - (start)) <= (sv).len), (StringView) {\
    .data = (sv).data + (start),\
    .len = (end) - (start),\
})

#define sv_split(sv, i)\
(_COLLECTIONS_STRING_VIEW_ASSERT((i) < (sv).len), (StringViewPair) {\
    .left = (StringView) {\
        .data = (sv).data,\
        .len = (i),\
    },\
    .right = (StringView) {\
        .data = (sv).data + (i),\
        .len = (sv).len - (i),\
    }\
})

#define sv_chop(sv, n)\
(_COLLECTIONS_STRING_VIEW_ASSERT((n) <= (sv).len), (StringView) {\
    .data = (sv).data + (n),\
    .len = (sv).len - (n)\
})

#define sv_chop_end(sv, n)\
(_COLLECTIONS_STRING_VIEW_ASSERT((n) <= (sv).len), (StringView) {\
    .data = (sv).data,\
    .len = (sv).len - (n)\
})

#define sv_trim_matches(sv, matches) sv_trim_end_matches(sv_trim_start_matches((sv), (matches)).right, (matches)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_matches(StringView sv, int (*matches)(int));
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_matches(StringView sv, int (*matches)(int));
#define sv_chop_matches sv_trim_start_matches
#define sv_chop_end_matches sv_trim_end_matches

#define sv_trim_unless(sv, unless) sv_trim_end_unless(sv_trim_start_unless((sv), (unless)).right, (unless)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_unless(StringView sv, int (*unless)(int));
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_unless(StringView sv, int (*unless)(int));
#define sv_chop_unless sv_trim_start_unless
#define sv_chop_end_unless sv_trim_end_unless

// trim whitespace
#define sv_trim(sv) sv_trim_end(sv_trim_start((sv)).right).left
#define sv_trim_start(sv) sv_trim_start_matches((sv), _COLLECTIONS_STRING_VIEW_ISSPACE)
#define sv_trim_end(sv) sv_trim_end_matches((sv), _COLLECTIONS_STRING_VIEW_ISSPACE)

#define sv_trim_while(sv, pat) sv_trim_end_while(sv_trim_start_while((sv), (pat)).right, (pat)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_while(StringView sv, const char* pat);
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_while(StringView sv, const char* pat);
#define sv_chop_while sv_trim_start_while
#define sv_chop_end_while sv_trim_end_while

#define sv_trim_until(sv, pat) sv_trim_end_until(sv_trim_start_until((sv), (pat)).right, (pat)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_until(StringView sv, const char* pat);
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_until(StringView sv, const char* pat);
#define sv_chop_until sv_trim_start_until
#define sv_chop_end_until sv_trim_end_until

#define sv_trim_whilec(sv, c) sv_trim_end_whilec(sv_trim_start_whilec((sv), (c)).right, (c)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_whilec(StringView sv, char c);
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_whilec(StringView sv, char c);
#define sv_chop_whilec sv_trim_start_whilec
#define sv_chop_end_whilec sv_trim_end_whilec

#define sv_trim_untilc(sv, c) sv_trim_end_untilc(sv_trim_start_untilc((sv), (c)).right, (c)).left
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_untilc(StringView sv, char c);
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_untilc(StringView sv, char c);
#define sv_chop_untilc sv_trim_start_untilc
#define sv_chop_end_untilc sv_trim_end_untilc

#endif // ___COLLECTIONS_STRING_VIEW_HEADER

#ifdef COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#ifndef ___COLLECTIONS_STRING_VIEW_IMPLEMENTATION
#define ___COLLECTIONS_STRING_VIEW_IMPLEMENTATION

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_matches(StringView sv, int (*matches)(int)) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        if (matches(sv.data[i])) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_matches(StringView sv, int (*matches)(int)) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        if (matches(sv.data[len - 1])) {
            len--;
        } else {
            break;
        }
    }

    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}


_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_unless(StringView sv, int (*unless)(int)) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        if (!unless(sv.data[i])) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_unless(StringView sv, int (*unless)(int)) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        if (!unless(sv.data[len - 1])) {
            len--;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_while(StringView sv, const char* pat) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T pat_len = _COLLECTIONS_STRING_VIEW_STRLEN(pat);
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        int matches = 0;
        for (_COLLECTIONS_STRING_VIEW_SIZE_T j = 0; j < pat_len; j++) {
            if (sv.data[i] == pat[j]) {
                matches = 1;
                break;
            }
        }
        if (matches) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_while(StringView sv, const char* pat) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T pat_len = _COLLECTIONS_STRING_VIEW_STRLEN(pat);
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        int matches = 0;
        for (_COLLECTIONS_STRING_VIEW_SIZE_T j = 0; j < pat_len; j++) {
            if (sv.data[len - 1] == pat[j]) {
                matches = 1;
                break;
            }
        }
        if (matches) {
            len--;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_until(StringView sv, const char* pat) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T pat_len = _COLLECTIONS_STRING_VIEW_STRLEN(pat);
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        int matches = 0;
        for (_COLLECTIONS_STRING_VIEW_SIZE_T j = 0; j < pat_len; j++) {
            if (sv.data[i] == pat[j]) {
                matches = 1;
                break;
            }
        }
        if (!matches) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}
_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_until(StringView sv, const char* pat) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T pat_len = _COLLECTIONS_STRING_VIEW_STRLEN(pat);
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        int matches = 0;
        for (_COLLECTIONS_STRING_VIEW_SIZE_T j = 0; j < pat_len; j++) {
            if (sv.data[len - 1] == pat[j]) {
                matches = 1;
                break;
            }
        }
        if (!matches) {
            len--;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_whilec(StringView sv, char c) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        if (sv.data[i] == c) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_whilec(StringView sv, char c) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        if (sv.data[len - 1] == c) {
            len--;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_start_untilc(StringView sv, char c) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T i = 0;
    while (i < sv.len) {
        if (sv.data[i] != c) {
            i++;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = i
        },

        .right = (StringView) {
            .data = sv.data + i,
            .len = sv.len - i
        }
    };
}

_COLLECTIONS_STRING_VIEW_APIDEF StringViewPair sv_trim_end_untilc(StringView sv, char c) {
    if (sv.len == 0) return (StringViewPair) { .l = sv, .r = sv };
    _COLLECTIONS_STRING_VIEW_SIZE_T len = sv.len;
    while (len > 0) {
        if (sv.data[len - 1] != c) {
            len--;
        } else {
            break;
        }
    }
    return (StringViewPair) {
        .left = (StringView) {
            .data = sv.data,
            .len = len
        },

        .right = (StringView) {
            .data = sv.data + len,
            .len = sv.len - len
        }
    };
}
#endif // ___COLLECTIONS_STRING_VIEW_IMPLEMENTATION
#endif // COLLECTIONS_IMPORT_STRING_VIEW_IMPLEMENTATION
#endif //  COLLECTIONS_IMPORT_STRING_VIEW

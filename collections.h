/** @file collections.h
    The main source file of collections.h.
*/

#ifndef ___COLLECTIONS_H_DEFAULT_FMT_ARG
#define ___COLLECTIONS_H_DEFAULT_FMT_ARG(x) (x)
#endif // ___COLLECTIONS_H_DEFAULT_FMT_ARG

#ifdef COLLECTIONS_IMPORT
#define COLLECTIONS_IMPORT_LIST
#define COLLECTIONS_IMPORT_STRMAP
#endif // COLLECTIONS_IMPORT

#ifdef COLLECTIONS_IMPORT_IMPLEMENTATION
#define COLLECTIONS_IMPORT_LIST_IMPLEMENTATION
#define COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION
#endif // COLLECTIONS_IMPORT_IMPLEMENTATION

#ifndef _COLLECTIONS_ASSERT
#define _COLLECTIONS_ASSERT assert
#endif // _COLLECTIONS_ASSERT

#ifndef _COLLECTIONS_REALLOC
#define _COLLECTIONS_REALLOC realloc
#endif // _COLLECTIONS_REALLOC

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

#ifndef _COLLECTIONS_STRCMP
#define _COLLECTIONS_STRCMP strcmp
#endif // _COLLECTIONS_STRCMP

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

#ifdef __SIZE_TYPE__
#define ___COLLECTIONS_LIST_SIZE_T __SIZE_TYPE__
#else // __SIZE_TYPE__
// fallback to size_t
#define ___COLLECTIONS_LIST_SIZE_T size_t
#endif // __SIZE_TYPE__
/** @endcond */

/** @brief Helper macro that add necessary list fields of type `ty` to your struct so it can interact with list macros */
#define LIST_FIELDS(ty)\
ty* data;\
___COLLECTIONS_LIST_SIZE_T len;\
___COLLECTIONS_LIST_SIZE_T cap

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
    for (___COLLECTIONS_LIST_SIZE_T i = 0; i < (src)->len; ++i) {\
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
    for (___COLLECTIONS_LIST_SIZE_T i = 1; i < (list)->len; i++) {\
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

#ifdef __SIZE_TYPE__
#define ___COLLECTIONS_STRMAP_SIZE_T __SIZE_TYPE__
#else // __SIZE_TYPE__
// fallback to size_t
#define ___COLLECTIONS_STRMAP_SIZE_T size_t
#endif // __SIZE_TYPE__
/** @endcond */

#define StrMap(ty)\
struct {\
    struct {\
        char* key;\
        int marker;\
    }* keys;\
    ty* data;\
    ___COLLECTIONS_STRMAP_SIZE_T _data_field_size;\
    ___COLLECTIONS_STRMAP_SIZE_T _key_field_size;\
    ___COLLECTIONS_STRMAP_SIZE_T len;\
    ___COLLECTIONS_STRMAP_SIZE_T cap;\
}

void* ___strmap_put(void* map, const char* key, void* data, ___COLLECTIONS_STRMAP_SIZE_T data_size);
void* ___strmap_get(void* map, const char* key);
int ___strmap_remove(void* map, const char* key, void* out);

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
    ___COLLECTIONS_STRMAP_SIZE_T found = 0;\
    for (___COLLECTIONS_STRMAP_SIZE_T i = 0; i < (map)->cap; i++) {\
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
    ___COLLECTIONS_STRMAP_SIZE_T __collections_h_iter_found = 0;\
    for (___COLLECTIONS_STRMAP_SIZE_T __collections_h_iter_i = 0; __collections_h_iter_i < (map)->cap; __collections_h_iter_i++) {\
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
    ___COLLECTIONS_STRMAP_SIZE_T _data_field_size;
    ___COLLECTIONS_STRMAP_SIZE_T _key_field_size;
    ___COLLECTIONS_STRMAP_SIZE_T len;
    ___COLLECTIONS_STRMAP_SIZE_T cap;
};

// https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
unsigned long ___strmap_djb2(const char *str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;

}

___COLLECTIONS_STRMAP_SIZE_T ___strmap_index(struct ___Collections_StrMap_Generic* map, const char* key) {
    ___COLLECTIONS_STRMAP_SIZE_T index = ___strmap_djb2(key) & (map->cap - 1);
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

void* ___strmap_put(void* map, const char* key, void* data, ___COLLECTIONS_STRMAP_SIZE_T data_size) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if ((map_->len + 1) >= map_->cap) {
        if (map_->cap == 0) map_->_data_field_size = data_size;
        map_->cap = map_->cap == 0 ? 16 : map_->cap * 2;
        map_->data = _COLLECTIONS_STRMAP_REALLOC(map_->data, map_->cap * map_->_data_field_size);
        map_->keys = _COLLECTIONS_STRMAP_REALLOC(map_->keys, map_->cap * sizeof(*map_->keys));
    }
    ___COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
    if (index > map_->cap) return NULL;
    char* map_data = (char*)map_->data + map_->_data_field_size * index;
    _COLLECTIONS_STRMAP_MEMCPY(map_data, data, map_->_data_field_size);
    map_->keys[index].key = _COLLECTIONS_STRMAP_STRDUP(key);
    map_->keys[index].marker = 1;
    map_->len++;

    return map_data;
}

void* ___strmap_get(void* map, const char* key) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if (map_->cap == 0 || map_->len == 0 || map_->data == NULL) return NULL;
    ___COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
    if (index >= map_->cap) return NULL;
    if (map_->keys[index].marker != 1) return NULL;
    char* map_data = (char*)map_->data + map_->_data_field_size * index;

    return map_data;
}

int ___strmap_remove(void* map, const char* key, void* out) {
    struct ___Collections_StrMap_Generic* map_ = map;
    if (map_->cap == 0 || map_->len == 0 || map_->data == NULL) return 0;
    ___COLLECTIONS_STRMAP_SIZE_T index = ___strmap_index(map, key);
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

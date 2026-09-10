/*
 * 01-strmap : Example showcasing basic usage of the StrMap module
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COLLECTIONS_IMPORT_STRMAP
#define COLLECTIONS_IMPORT_STRMAP_IMPLEMENTATION
#include "../../collections.h"

int main(void) {
    StrMap(float) weights = {0};

    strmap_put(&weights, "a", 1.0);
    strmap_put(&weights, "b", 2.0);
    strmap_put(&weights, "c", 3.0);
    strmap_put(&weights, "d", 4.0);

    strmap_dbg(&weights, "%f");

    float item;
    if (strmap_remove(&weights, "d", &item)) {
        printf("Removed key with weight '%f'\n", item);
    }

    strmap_iter(&weights, key_iter, val_iter, {
        printf("Key '%s' has weight '%f'\n", key_iter, *val_iter);
    });

    strmap_free(&weights);
    return 0;
}

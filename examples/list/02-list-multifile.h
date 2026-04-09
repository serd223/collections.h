/*
 * 02-list-multifile : Example showcasing encapsulation while using the List module
*/

#pragma once

// Typically you should avoid including module implementations in your header files
// Though even if you do import implementations, they are guaranteed to be
// included only once
#define COLLECTIONS_IMPORT_LIST
#include <stddef.h>
#include "../../collections.h"

TYPEDEF_LIST(float, Weights);

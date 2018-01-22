#ifndef HOLD_ARRAYLIST_H__
#define HOLD_ARRAYLIST_H__

#include "element.h"


typedef struct
{
  element       *array;         // 8 bytes
  size_t         capacity;      // 8 bytes
  size_t         length;        // 8 bytes
} arraylist;

/**
 * Initialize an arraylist with an initial capacity `cap`.
 */
void
arraylist_init (arraylist *a, size_t cap);

void
arraylist_deinit (arraylist *a);

void
arraylist_add (arraylist *a, element el);

static inline void *
arraylist_getp (arraylist *a, size_t i)
{
  return a->array[i].pointer;
}

static inline uint64_t
arraylist_getu (arraylist *a, size_t i)
{
  return a->array[i].u;
}

#endif  // HOLD_ARRAYLIST_H__

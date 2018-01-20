#ifndef HOLD_ARRAYLIST_H__
#define HOLD_ARRAYLIST_H__

#include "element.h"


struct arraylist
{
  element       *array;         // 8 bytes
  size_t         capacity;      // 8 bytes
  size_t         length;        // 8 bytes
};

typedef struct arraylist *arraylistp;

/**
 * Initialize an arraylist with an initial capacity `cap`.
 */
void
arraylist_init (arraylistp a, size_t cap);

void
arraylist_deinit (arraylistp a);

void
arraylist_add (arraylistp a, element el);

#endif  // HOLD_ARRAYLIST_H__

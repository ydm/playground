#ifndef HOLD_ELEMENT_H__
#define HOLD_ELEMENT_H__

#include "common.h"

typedef union
{
  int8_t    bytes[8];
  void     *pointer;
  uint64_t  u;
} element;

/* Element callbacks */
typedef void (*element_cb) (element);
typedef void (*elements_cb) (const element[], size_t);

static inline void
element_swap (element ary[], size_t a, size_t b)
{
  element t = ary[a];
  ary[a] = ary[b];
  ary[b] = t;
}

#endif  // HOLD_ELEMENT_H__

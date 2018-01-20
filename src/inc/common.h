#ifndef HOLD_COMMON_H__
#define HOLD_COMMON_H__

// Common includes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Functions
void
die (const char *err, ...)
  __attribute__ ((format (printf, 1, 2)))
  __attribute__ ((noreturn));

// Objects lifecycle:
//
// alloc --> init --> deinit --> dealloc
// new == alloc + init

#endif // HOLD_COMMON_H__

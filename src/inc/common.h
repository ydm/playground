#ifndef PLAY_COMMON_H__
#define PLAY_COMMON_H__

// Common includes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Functions
void
die (const char *err, ...)
  __attribute__ ((format (printf, 1, 2)))
  __attribute__ ((noreturn));


#define UNUSED __attribute__((unused))

// Objects lifecycle:
//
// alloc --> init --> deinit --> dealloc
// new == alloc + init

#endif // PLAY_COMMON_H__

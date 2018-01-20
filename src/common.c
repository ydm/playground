#include <stdarg.h>             // va_list
#include <stdio.h>              // fputs, vfprintf
#include <stdlib.h>             // exit

#include "common.h"

void
die (const char *err, ...)
{
  fputs ("fatal: ", stderr);

  va_list params;
  va_start (params, err);
  vfprintf (stderr, err, params);
  va_end (params);

  fputs ("\n", stderr);
  exit (EXIT_FAILURE);
}

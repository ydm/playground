#include <stdlib.h>
#include "drawables.h"


struct drawables *
drawables_new (struct program *prog)
{
  struct drawables *ds = malloc (sizeof (struct drawables));
  ds->prog = prog;
  return ds;
}

void
drawables_dealloc (struct drawables *ds)
{
  free (ds);
}

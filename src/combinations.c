#include <stdlib.h>
#include "combinations.h"

#include <stdio.h>


combinationsp
combinations_new (element pool[], size_t n, size_t k)
{
  combinationsp c = malloc (sizeof (struct combinations));
  c->pool = pool;
  c->indices = calloc (n, sizeof (size_t));
  c->result = NULL;
  c->n = n;
  c->k = k;

  for (size_t i = 0; i < n; i++)
    c->indices[i] = i;

  return c;
}

void
combinations_dealloc (combinationsp c)
{
  free (c->result);
  free (c->indices);
  free (c);
}

bool
combinations_next (combinationsp c)
{
  if (c->result == NULL)
    {
      c->result = calloc (c->k, sizeof (element));
      for (size_t i = 0; i < c->k; i++)
	{
	  size_t index = c->indices[i];
	  c->result[i] = c->pool[index];
	}
      return true;
    }
  else
    {
      size_t i = 0;
      for (i = (c->k - 1); c->indices[i] == (i + c->n - c->k); i--)
	if (i == 0)
	  return false;
      c->indices[i] += 1;
      for (size_t j = (size_t) i + 1; j < c->k; j++)
	c->indices[j] = c->indices[j-1] + 1;
      for (; i < c->k; i++)
	{
	  size_t index = c->indices[i];
	  c->result[i] = c->pool[index];
	}
      return true;
    }
}

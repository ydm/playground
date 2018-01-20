#include <stdlib.h>
#include "hashset.h"


struct hashset *
hashset_new (hashset_hash_fn hash, hashset_eq_fn eq)
{
  hashsetp ans = malloc (sizeof (struct hashset));
  for (size_t i = 0; i < 128; i++)
    arraylist_init (ans->data + i, 8);
  ans->hash = hash;
  ans->eq = eq;
  return ans;
}

void
hashset_dealloc (hashsetp set)
{
  for (size_t i = 0; i < 128; i++)
    {
      arraylist_deinit (set->data + i);
    }
  free (set);
}

void
hashset_add (hashsetp set, element e)
{
  if (hashset_contains (set, e) == false)
    {
      int32_t hash = set->hash (e);
      size_t index = (size_t) hash % 128u;
      // printf("index=%d\n", index);
      arraylist_add (set->data + index, e);
    }
}

bool
hashset_contains (hashsetp set, element e)
{
  int32_t hash = set->hash (e);
  size_t index = (size_t) hash % 128u;  
  arraylistp ary = set->data + index;

  for (size_t i = 0; i < ary->length; i++)
    if (set->eq (ary->array[i], e))
      return true;
  return false;
}

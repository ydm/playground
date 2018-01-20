#include <assert.h>	      /* TODO: REMOVE! See arraylist_add () */
#include <stdlib.h>

#include "arraylist.h"


void
arraylist_init (arraylistp a, size_t cap)
{
	a->array = calloc (sizeof (element), cap);
	a->capacity = cap;
	a->length = 0;
}

void
arraylist_deinit (arraylistp a)
{
	free (a->array);
	a->array = NULL;
}

void
arraylist_add (arraylistp a, element e)
{
	// TODO: Instead of asserting, enlarge capacity if needed!
	assert (a->length < a->capacity);
	a->array[a->length++] = e;
}

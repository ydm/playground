#include <assert.h>	      /* TODO: REMOVE! See arraylist_add () */
#include <stdlib.h>

#include "arraylist.h"


void
arraylist_init (arraylist *a, size_t cap)
{
	a->array = calloc (sizeof (element), cap);
	a->capacity = cap;
	a->length = 0;
}

void
arraylist_deinit (arraylist *a)
{
	free (a->array);
	a->array = NULL;
}

void
arraylist_add (arraylist *a, element e)
{
	// TODO: Instead of asserting, enlarge capacity if needed!
	assert (a->length < a->capacity);
	a->array[a->length++] = e;
}

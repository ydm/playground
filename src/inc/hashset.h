#ifndef HOLD_HASHSET_H__
#define HOLD_HASHSET_H__

#include "arraylist.h"


typedef bool    (*hashset_eq_fn)   (element, element);
typedef int32_t (*hashset_hash_fn) (element);

struct hashset
{
	struct arraylist data[128];   // 128 * 24 = 3072 bytes
	hashset_hash_fn hash;	      // 8 bytes
	hashset_eq_fn eq;	      // 8 bytes
};

typedef struct hashset *hashsetp;

hashsetp
hashset_new (hashset_hash_fn, hashset_eq_fn);

void
hashset_dealloc (hashsetp set);

void
hashset_add (hashsetp set, element el);

bool
hashset_contains (hashsetp set, element el);

#endif  // HOLD_HASHSET_H__

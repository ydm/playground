#ifndef HOLD_COMBINATIONS_H__
#define HOLD_COMBINATIONS_H__

#include "element.h"


// Copied from Python's itertoolsmodule.c
struct combinations
{
  element       *pool;	  // Input array
  size_t        *indices; // One index per result element
  element       *result;  // Gets modified on each call to next ()
  size_t         n;	  // Size of input
  size_t         k;	  // Size of result
};


typedef struct combinations *combinationsp;


combinationsp
combinations_new (element pool[], size_t n, size_t k);

void
combinations_dealloc (combinationsp);

bool
combinations_next (combinationsp c);

#endif  // HOLD_COMBINATIONS_H__

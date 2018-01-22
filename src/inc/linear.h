#ifndef PLAY_LINEAR_H__
#define PLAY_LINEAR_H__

#include "common.h"
#include "gl.h"
#include <string.h>


/*
 * vectors
 */
typedef union {
  GLfloat v[3];
  struct { GLfloat x, y, z; };
} vec3;
typedef vec3 *vec3p;
// typedef GLfloat vec4[4];

static inline void
vec3_multf (const vec3p a, GLfloat b, vec3p o)
{
  o->x = a->x * b;
  o->y = a->y * b;
  o->z = a->z * b;
}

static inline void
vec3_plus (const vec3p a, const vec3p b, vec3p o)
{
  o->x = a->x + b->x;
  o->y = a->y + b->y;
  o->z = a->z + b->z;
}

void
vec3_print (const vec3p v);


/*
 * matrices
 */

/**
 * Matrix indices
 *
 *   x  y   z   w
 * { 0, 4,  8, 12,
 *   1, 5,  9, 13,
 *   2, 6, 10, 14,
 *   3, 7, 11, 15 }
 */
typedef GLfloat mat4[16];

/**
 * NB: IDENTITY isn't const but should never be changed!
 */
static mat4 IDENTITY = {
  1.0f, 0.0f, 0.0f, 0.0f,  // x
  0.0f, 1.0f, 0.0f, 0.0f,  // y
  0.0f, 0.0f, 1.0f, 0.0f,  // z
  0.0f, 0.0f, 0.0f, 1.0f,  // w
};

static inline void
mat4_ident (mat4 m)
{
  memcpy (m, IDENTITY, 16 * sizeof (GLfloat));
}

bool
mat4_inv (mat4 in, mat4 out);

static inline void
mat4_translate3f (mat4 m, GLfloat x, GLfloat y, GLfloat z)
{
  mat4_ident (m);
  m[12] = x;
  m[13] = y;
  m[14] = z;
}

static inline void
mat4_translate3v (mat4 m, const vec3p v)
{
  mat4_ident (m);
  memcpy (m + 12, v, 3 * sizeof (GLfloat));
}

#endif  // PLAY_LINEAR_H__

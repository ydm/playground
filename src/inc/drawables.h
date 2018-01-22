#ifndef PLAY_DRAWABLE_H__
#define PLAY_DRAWABLE_H__

// #include "shaders.h"

struct program;

/*
struct drawable
{
};
*/

struct drawables
{
  struct program *prog;
};

struct drawables *
drawables_new (struct program *prog);

void
drawables_dealloc (struct drawables *ds);

void
drawables_draw (struct drawables *ds);

#endif  // PLAY_DRAWABLE_H__

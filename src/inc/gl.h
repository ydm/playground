#ifndef PLAY_GL_H__
#define PLAY_GL_H__

// glew.h should always be included before glfw3.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * Checks if there's a GL error and prints it out, then die()s.
 */
void checkgl_ (const char *);

// #ifndef NDEBUG
#if 1
#  define checkgl checkgl_
#else
#  define checkgl(x)
#endif

#endif  // PLAY_GL_H__

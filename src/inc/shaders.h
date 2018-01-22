#ifndef PLAY_SHADER_H__
#define PLAY_SHADER_H__
#include <stdio.h>
#include "arraylist.h"
#include "linear.h"
#include "gl.h"


struct program
{
  arraylist shaders;
  GLuint pid;
  int8_t _pad[4];
};

struct program *
program_new (void);

void
program_dealloc (struct program *p);

void
program_shader (struct program *p, const char *filename);

static inline void
program_link (struct program *p)
{
  glLinkProgram (p->pid);
  checkgl ("glLinkProgram");
  GLint status = GL_FALSE;
  glGetProgramiv (p->pid, GL_LINK_STATUS, &status);
  assert (status == GL_TRUE);
}

static inline void
program_use (struct program *p)
{
  glUseProgram (p->pid);
  checkgl ("glUseProgram");
}

static inline void
program_umat4 (struct program *p, const GLchar *name, mat4 m)
{
  GLint loc = glGetUniformLocation (p->pid, name);
  checkgl ("glGetUniformLocation");
  glUniformMatrix4fv (loc, 1, GL_FALSE, m);
  checkgl ("glUniformMatrix4fv");
}

#endif  // PLAY_SHADER_H__

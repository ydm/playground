#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shaders.h"


/*
 * private
 */

static void
infolog (GLuint id)
{
  GLint len = 0;
  glGetShaderiv (id, GL_INFO_LOG_LENGTH, &len);
  GLchar *log = malloc ((size_t) len * sizeof (GLchar));
  glGetShaderInfoLog (id, (GLsizei) len, NULL, log);
  printf ("%s", log);
  free (log);
}

static char *
read (const char *filename)
{
  FILE *f = fopen (filename, "rb");
  if (f == NULL)
    {
      return NULL;
    }
  int seek = fseek (f, 0, SEEK_END);
  assert(seek == 0);
  size_t count = (size_t) ftell (f);
  char *ans = malloc (count + 1);
  rewind (f);
  size_t read = fread (ans, 1, count, f);
  ans[count] = '\0';
  assert (read == count);
  fclose (f);
  return ans;
}

static void
initshader (GLuint sh, const char *filename)
{
  char *source = read (filename);
  GLint len = -1;
  const GLchar *sources[] = { (GLchar *) source };
  glShaderSource (sh, 1, sources, &len);
  checkgl ("glShaderSource");

  GLboolean supported = GL_FALSE;
  glGetBooleanv (GL_SHADER_COMPILER, &supported);
  if (supported != GL_TRUE)
    {
      die ("shader compilation is not supported");
    }

  glCompileShader (sh);
  checkgl ("glCompileShader");

  GLint status = GL_FALSE;
  glGetShaderiv (sh, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE)
    {
      infolog (sh);
      die ("failed to compile");
    }
  free (source);
}

GLuint
shadertype (const char *filename)
{
  // XXX: Is it better for these to be static?
  const char *exts[] = {
    ".frag",
    ".vert",
  };
  GLuint types[] = {
    GL_FRAGMENT_SHADER,
    GL_VERTEX_SHADER,
  };
  while (*filename != '\0')
    filename++;
  filename -= 5;
  for (size_t i = 0; i < 2; i++)
    {
      if (strncmp (filename, exts[i], 5) == 0)
        {
          return types[i];
        }
    }
  die ("unable to determine shader type by filename=%s", filename);
}


/*
 * program
 */

struct program *
program_new (void)
{
  struct program *prog = malloc (sizeof (struct program));
  arraylist_init (&prog->shaders, 8);
  prog->pid = glCreateProgram ();
  checkgl ("glCreateProgram");
  return prog;
}

void
program_dealloc (struct program *p)
{
  for (size_t i = 0; i < p->shaders.length; i++)
    {
      GLuint sh = (GLuint) arraylist_getu (&p->shaders, i);
      glDetachShader (p->pid, sh);
      checkgl ("glDetachShader");
      glDeleteShader (sh);
      checkgl ("glDeleteShader");
    }
  arraylist_deinit (&p->shaders);

  glDeleteProgram(p->pid);
  checkgl ("glDeleteProgram");
  p->pid = 0;

  free (p);
}

void
program_shader (struct program *p, const char *filename)
{
  GLuint tp = shadertype (filename);
  GLuint sh = glCreateShader (tp);
  checkgl ("glCreateShader");
  glAttachShader (p->pid, sh);
  checkgl ("glAttachShader");
  initshader (sh, filename);

  element e = { .u = sh };
  arraylist_add (&p->shaders, e);
}

// #include <signal.h>
#include "common.h"
#include "gl.h"


void
checkgl_ (const char *p)
{
  GLenum err = glGetError ();
  if (err != GL_NO_ERROR)
    {
      // signal (SIGTSTP, SIG_DFL);
      die ("%s: %s (%d)",
           p ? p : "GL error",
           gluErrorString (err), (int) err);
    }
}

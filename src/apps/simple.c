#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "application.h"
#include "camera.h"
#include "shaders.h"
#include <GL/glew.h>


/*
 * private
 */

struct data
{
  struct camera   cam;
  struct program *prog;
  // GLuint *varys;  // Vertex arrays
  GLuint vao;
  GLuint vbo;
};


static struct application *app = NULL;

/*
 * TODO: DELETE!
 */
static const GLfloat points[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
  -1.0f,  1.0f, 0.0f,
   1.0f,  1.0f, 0.0f
};
/*
static const GLfloat colors[] = {
  1.0f, 0.5f, 0.5f,
  0.5f, 1.0f, 0.5f,
  0.5f, 0.5f, 1.0f,
  1.0f, 1.0f, 1.0f,
};
*/


/*
 * Callback functions
 */
static void
charfun (UNUSED GLFWwindow *window, unsigned codepoint)
{
  printf ("charfun: codepoint=%u\n", codepoint);
}

static void
cursorposfun (UNUSED GLFWwindow *window, double xpos, double ypos)
{
  printf ("cursorposfun: xpos=%f ypos=%f\n", xpos, ypos);
}

static void
keyfun (UNUSED GLFWwindow *window, int key, int scancode, int action, int mods)
{
  /*
  printf ("keyfun: key=%d scancode=%d action=%d mods=%d\n",
          key, scancode, action, mods);
  */
  struct data *d = app->data;
  switch (key)
    {
    case GLFW_KEY_W: d->cam.forward  = (action != 0); break;
    case GLFW_KEY_A: d->cam.left     = (action != 0); break;
    case GLFW_KEY_S: d->cam.backward = (action != 0); break;
    case GLFW_KEY_D: d->cam.right    = (action != 0); break;
    }
}

static void
mousebuttonfun (UNUSED GLFWwindow *window, int button, int action, int mods)
{
  printf ("mousebuttonfun: button=%d action=%d mods=%d\n",
          button, action, mods);
}


/*
 * App
 */

static void
initfun (void *p)
{
  struct data *d = p;

  glEnable (GL_DEPTH_TEST);
  /* glEnable (GL_CULL_FACE); */
  /* glCullFace (GL_BACK); */

  printf ("OpenGL %s\n", glGetString (GL_VERSION));
  printf ("GLSL %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

  d->prog = program_new ();
  program_shader (d->prog, "shaders/standart.vert");
  program_shader (d->prog, "shaders/standart.frag");
  program_link (d->prog);

  // Set uniforms
  program_use (d->prog);
  mat4 model;
  mat4_translate3f (model, 0.0f, 0.0f, 0.0f);
  program_umat4 (d->prog, "u_model", model);
  program_umat4 (d->prog, "u_view",  IDENTITY);
  program_umat4 (d->prog, "u_proj",  IDENTITY);

  // Fill geometry buffers
  glGenVertexArrays (1, &d->vao);
  checkgl ("glGenVertexArrays");
  assert (d->vao != 0);
  glBindVertexArray (d->vao);
  {
    glGenBuffers (1, &d->vbo);
    checkgl ("glGenBuffers");
    assert (d->vbo != 0);

    glBindBuffer (GL_ARRAY_BUFFER, d->vbo);
    {
      glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (GLfloat), points,
                    GL_STATIC_DRAW);
      glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
      glEnableVertexArrayAttrib (d->vao, 0);
    }
    // XXX?: glBindBuffer (GL_ARRAY_BUFFER, 0);
  }
  // XXX?: glBindVertexArray (0);
}

static void
deinitfun (void *p)
{
  printf ("DEINITFUN\n");
  struct data *d = p;
  program_dealloc (d->prog);
}

static void
updatefun (void *p, float dt)
{
  struct data *d = p;
  if (camera_update (&d->cam, dt))
    {
      program_use (d->prog);
      program_umat4 (d->prog, "u_view", d->cam.view);
      program_umat4 (d->prog, "u_proj", d->cam.proj);
      vec3_print (&d->cam.pos); putchar ('\n');
    }
}

static void
drawfun (void *p)
{
  struct data *d = p;
  program_use (d->prog);

  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBindVertexArray (d->vao);
  glDrawArrays (GL_TRIANGLE_STRIP, 0, 6);
}


struct application *
simple_app ()
{
  app = app_alloc ();

  app->charfun        = charfun;
  app->cursorposfun   = cursorposfun;
  app->keyfun         = keyfun;
  app->mousebuttonfun = mousebuttonfun;

  app->initfun        = initfun;
  app->deinitfun      = deinitfun;
  app->updatefun      = updatefun;
  app->drawfun        = drawfun;

  struct data *d = malloc (sizeof (struct data));
  app->data = d;

  memset (d, 0, sizeof (struct data));
  camera_init (&d->cam);

  printf ("CAM SIZE: %zu\n", sizeof (struct camera));

  return app;
}

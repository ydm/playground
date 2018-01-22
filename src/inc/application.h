#ifndef PLAY_APPLICATION_H__
#define PLAY_APPLICATION_H__

/* stdlib.h and string.h needed for app_alloc() and app_dealloc() */
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "gl.h"


typedef void (*app_datafun) (void *data);
typedef void (*app_updatefun) (void *data, float dt);

/**
 * Application lifecycle:
 *
 * (alloc)            ->
 * (init)             ->
 * (deploy)           ->
 * (draw many times)  ->
 * (deinit)           ->
 * (dealloc)
 */
struct application
{
  GLFWcharfun         charfun;
  GLFWcursorposfun    cursorposfun;
  GLFWkeyfun          keyfun;
  GLFWmousebuttonfun  mousebuttonfun;

  app_datafun         initfun;
  app_datafun         deinitfun;

  app_updatefun       updatefun;
  app_datafun         drawfun;

  void               *data;
};

static inline struct application *
app_alloc ()
{
  struct application *app = malloc (sizeof (struct application));
  memset (app, 0, sizeof (struct application));
  return app;
}

static inline void
app_init (struct application *app)
{
  app->initfun (app->data);
}

static inline void
app_deinit (struct application *app)
{
    app->deinitfun (app->data);
}

static inline void
app_dealloc (struct application *app)
{
  free (app);
}

static inline void
app_deploy (GLFWwindow *w, struct application *app)
{
  glfwSetCharCallback        (w, app->charfun       );
  glfwSetCursorPosCallback   (w, app->cursorposfun  );
  glfwSetKeyCallback         (w, app->keyfun        );
  glfwSetMouseButtonCallback (w, app->mousebuttonfun);
  /*
  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glfwSetScrollCallback(window, scrollCallback);
  */
}

static inline void
app_draw (struct application *app)
{
  app->drawfun (app->data);
}

static inline void
app_update (struct application *app, float dt)
{
  app->updatefun (app->data, dt);
}

#endif  // PG_APPLICATION_H__

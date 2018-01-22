#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "application.h"
#include "apps/simple.h"


int
main ()
{
  int ret = 0;

  // 1. Init GLFW
  if (glfwInit () != GLFW_TRUE)
    exit (EXIT_FAILURE);

  // 2. Create window
  GLFWwindow *window = glfwCreateWindow (800, 800, "playground", NULL, NULL);
  if (window == NULL)
    {
      ret = EXIT_FAILURE;
      goto out1;
    }
  glfwMakeContextCurrent (window);

  // 3. Init GLEW
  if (glewInit () != GLEW_OK)
    {
      ret = EXIT_FAILURE;
      goto out2;
    }

  // 4. Create, deploy and init application
  struct application *app = simple_app ();
  app_deploy (window, app);
  app_init (app);

  // 5. Loop
  clock_t mark = clock ();
  while (glfwWindowShouldClose (window) == GLFW_FALSE)
    {
      glfwPollEvents ();

      clock_t now = clock ();
      float dt = (float) (now - mark) / (float) CLOCKS_PER_SEC;
      mark = now;

      if (__builtin_expect (dt > 0.0f, 1))
        {
          app_update (app, dt);
          app_draw (app);
          glfwSwapBuffers (window);
        }
    }

  // 4. Deinit application
  app_deinit (app);
  app_dealloc (app);
 out2:
  // 2. Destroy window
  glfwDestroyWindow (window);
 out1:
  // 1. Destroy GLFW
  glfwTerminate ();

  return ret;
}

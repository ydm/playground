#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "camera.h"


static vec3 DIRS[] = {
  {{ -1.0f,  0.0f,  0.0f }}, // left
  {{  1.0f,  0.0f,  0.0f }}, // right
  {{  0.0f, -1.0f,  0.0f }}, // down
  {{  0.0f,  1.0f,  0.0f }}, // up
  {{  0.0f,  0.0f, -1.0f }}, // forward
  {{  0.0f,  0.0f,  1.0f }}, // backward
};

void
camera_init (struct camera *c)
{
  memset (c, 0, sizeof (struct camera));
  mat4_ident (c->view);

  float aspect = 1.0f;
  float zfar = 100.0f;
  float znear = 0.1f;
  // float fovy = (float) M_PI / 3.0f;  // 60 degrees
  float fovy = (float) 1.57079632679489661923; // M_PI_2;  // 90 degrees
  float f = 1.0f / tanf (fovy / 2);
  mat4_ident (c->proj);
  // x
  c->proj[0] = f / aspect;
  // y
  c->proj[5] = f;
  // z
  c->proj[10] = (znear + zfar) / (znear - zfar);
  c->proj[11] = (2 * znear * zfar) / (znear - zfar);
  // w
  c->proj[14] = -1.0f;
}

void
camera_deinit (UNUSED struct camera *u)
{
  // NOOP
}

bool
camera_update (struct camera *c, float dt)
{
  bool change = false;
  for (size_t i = 0; i < 6; i++)
    {
      if (c->dirs & (1 << i))
        {
          vec3 delta = {{ 0.0f, 0.0f, 0.0f }};
          vec3_multf (DIRS + i, dt, &delta);
          vec3_plus (&c->pos, &delta, &c->pos);
          change = true;
        }
    }
  if (change)
    {
      mat4_translate3v (c->view, &c->pos);
      mat4_inv (c->view, c->view);
    }
  return change;
}

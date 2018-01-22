#ifndef PLAY_CAMERA_H__
#define PLAY_CAMERA_H__

#include "common.h"
#include "linear.h"


/*
enum cameradir
{
  CAM_LEFT, CAM_RIGHT,        // x
  CAM_DOWN, CAM_UP,           // y
  CAM_FORWARD, CAM_BACKWARD,  // z
};
*/

struct camera
{
  mat4 proj;                    //   0 + 64 bytes
  mat4 view;                    //  64 + 64 bytes
  vec3 pos;                     // 128 + 12 bytes
  union
  {
    struct
    {
      // x
      uint8_t left     : 1;
      uint8_t right    : 1;
      // y
      uint8_t down     : 1;
      uint8_t up       : 1;
      // z
      uint8_t forward  : 1;
      uint8_t backward : 1;
      // padding
      uint8_t _pad0    : 2;
    };
    uint8_t dirs;
  };                            // 140 + 1 bytes
  int8_t   _pad1[3];            // 141 + 3 bytes
};                              // 144 bytes in total

void camera_init (struct camera *);
void camera_deinit (struct camera *);
bool camera_update (struct camera *c, float dt);

// Matrices
void camera_view (struct camera *c, mat4 m);
void camera_proj (struct camera *c, mat4 m);

// Walking
/*
void camera_walk_start (struct camera *c, cameradir d);
void camera_walk_stop (struct camera *c, cameradir d);
*/

// Mouse
void camera_mouse_on (struct camera *c);
void camera_mouse_move (struct camera *c, const int x, const int y);
void camera_mouse_off (struct camera *c);

#endif  // PLAY_CAMERA_H__

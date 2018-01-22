#version 450 core

// Stage inputs
layout (location = 0) in vec3 i_color;

// Stage outputs
layout (location = 0 ) out vec3 o_color;

// Main
void main(void)
{
  // o_color = vec3(1.0, 0.0, 1.0);
  // o_color = i_color;
  o_color = vec3(i_color.x, i_color.y, 0.0f);
}

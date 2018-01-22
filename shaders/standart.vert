#version 450 core

// Uniforms
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

// Stage inputs
layout (location = 0) in vec3 i_vertex;

// Stage outputs
layout (location = 0) out vec3 o_color;

void main (void)
{
  // gl_Position = vec4(i_vertex.x - 0.15, i_vertex.y, i_vertex.z, 1.0f);
  // gl_Position = vec4(1.0, 0.0, 0.0, 1.0);
  gl_Position = u_proj * u_view * u_model * vec4(i_vertex, 1.0);
  o_color = i_vertex;
}

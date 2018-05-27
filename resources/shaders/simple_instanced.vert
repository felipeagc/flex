#version 300 es

precision mediump float;

uniform mat4 view;
uniform mat4 proj;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 tex_coords;
layout (location = 4) in mat4 model;

out vec3 color0;
out vec2 tex_coords0;

void main() {
  color0 = color;
  tex_coords0 = tex_coords;
  gl_Position = proj * view * model * vec4(pos, 1.0);
}

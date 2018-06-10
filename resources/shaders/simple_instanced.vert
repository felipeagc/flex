#version 300 es

precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;
layout (location = 3) in mat4 model_a;

out vec2 tex_coords0;

void main() {
  tex_coords0 = tex_coords;
  gl_Position = proj * view * model_a * model * vec4(pos, 1.0);
}

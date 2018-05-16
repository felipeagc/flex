#version 300 es

precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 color0;

void main() {
  color0 = color;
  gl_Position = proj * view * model * vec4(pos, 1.0);
}

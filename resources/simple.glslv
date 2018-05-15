#version 300 es

precision mediump float;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 color0;

void main() {
  color0 = color;
  gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}

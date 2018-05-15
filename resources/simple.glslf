#version 330 core

in vec3 color0;

out vec4 out_color;

void main() {
  out_color = vec4(color0.x, color0.y, color0.z, 1.0f);
}

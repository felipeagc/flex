#version 300 es

precision mediump float;

uniform sampler2D texture_diffuse0;
uniform bool is_textured;

in vec3 color0;
in vec2 tex_coords0;

out vec4 out_color;

void main() {
  out_color = vec4(color0, 1.0f);
  if (is_textured) {
    out_color *= texture2D(texture_diffuse0, tex_coords0);
  }
  // out_color = vec4(color0, 1.0f);
}

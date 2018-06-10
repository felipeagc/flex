#version 300 es

precision mediump float;

uniform sampler2D texture_diffuse0;
uniform bool is_textured;

in vec2 tex_coords0;

out vec4 out_color;

void main() {
  if (is_textured) {
    out_color = texture2D(texture_diffuse0, tex_coords0);
  } else {
    // TODO: change this
    out_color = vec4(1.0, 1.0, 1.0, 1.0);
  }
}

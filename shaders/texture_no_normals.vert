#version 400 core

attribute vec3 a_position;
attribute vec2 a_tex_coords;

out vec2 tex_coords;

uniform mat4 pvm;

void main() {
  tex_coords = a_tex_coords;
  gl_Position = pvm * vec4(a_position, 1.0);
}

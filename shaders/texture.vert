#version 400 core

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_tex_coords;

out vec3 view_pos;
out vec3 normal;
out vec2 tex_coords;

uniform mat4 pvm;
uniform mat4 vm;
uniform mat4 normal_mat;

void main() {
  view_pos = vec3(vm * vec4(a_position, 1.0));
  normal = normalize(mat3(normal_mat) * a_normal);
  tex_coords = a_tex_coords;
  gl_Position = pvm * vec4(a_position, 1.0);
}

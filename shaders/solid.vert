#version 400 core

attribute vec3 a_position;
attribute vec3 a_normal;

out vec3 view_pos;
out vec3 normal;

uniform mat4 pvm;
uniform mat4 vm;
uniform mat4 normal_mat;

void main() {
  normal = normalize(mat3(normal_mat) * a_normal);
  view_pos = vec3(vm * vec4(a_position, 1.0));
  gl_Position = pvm * vec4(a_position, 1.0);
}

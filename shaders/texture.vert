#version 400 core

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoords;

out vec3 pos;
out vec3 norm;
out vec2 tex;

uniform mat4 pvm;
uniform mat4 vm;
uniform mat4 matNormal;

void main() {
  gl_Position = pvm * vec4(position, 1.0);

  pos = vec3(vm * vec4(position, 1.0));
  norm = normalize(mat3(matNormal) * normal);

  tex = texCoords;
}

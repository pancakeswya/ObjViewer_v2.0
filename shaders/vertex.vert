#version 400 core

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoords;

out vec3 pos;
out vec3 norm;
out vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position =  projection * view  * model * vec4(position,1.0);

  mat3 matNormal = mat3(transpose(inverse(model)));
  pos = vec3(view  * model * vec4(position, 1.0));
  norm = matNormal * normal;

  tex = texCoords;
}

#version 400 core

attribute vec3 position;
attribute vec2 texCoords;

out vec2 tex;

uniform mat4 pvm;

void main() {
  gl_Position = pvm * vec4(position, 1.0);

  tex = texCoords;
}

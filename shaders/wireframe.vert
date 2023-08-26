#version 400 core

attribute vec3 a_position;

uniform mat4 pvm;

void main() { gl_Position = pvm * vec4(a_position, 1.0); }

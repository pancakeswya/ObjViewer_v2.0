#version 400 core

in vec2 tex;
uniform sampler2D texture1;

void main() { gl_FragColor = texture2D(texture1, tex); }

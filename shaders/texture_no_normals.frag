#version 400 core

in vec2 tex_coords;
uniform sampler2D texture_d;

void main() { gl_FragColor = texture2D(texture_d, tex_coords); }

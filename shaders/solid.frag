#version 400 core

in vec3 pos;
in vec3 norm;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ke;
uniform float specPower;
uniform float opacity;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform vec3 color;

void main() {
  vec3 lightDir = normalize(lightPos - pos.xyz);
  if (!gl_FrontFacing) {
      lightDir = -lightDir;
  }
  vec3 viewDir = normalize(viewPos - pos.xyz);
  vec3 reflectDir = reflect(-lightDir, norm);

  float diff = max(dot(norm, lightDir), 0.0f);
  float spec = pow(max(dot(norm, reflectDir), 0.0f), specPower);

  gl_FragColor = vec4(Ke + Ka + diff * (Kd + color) + Ks * spec, opacity);
}

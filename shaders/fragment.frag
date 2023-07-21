#version 400 core

in vec3 pos;
in vec3 norm;
in vec2 tex;

uniform vec3 Ka;
uniform float Kd;
uniform vec3 Ks;
uniform vec3 Ke;
uniform float specPower;
uniform float opacity;

uniform vec3 viewPos;

uniform bool use_texture;
uniform bool use_normals;
uniform vec3 color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  vec4 clr;
  if (use_texture) {
    clr = texture2D(texture1, tex);
  } else {
    clr = vec4(color, 1.0);
  }
  if (use_normals) {
    vec3 lightPos = vec3(2.5, 2.5, 2.5);
    vec3 lightCol = vec3(0.8, 0.8, 0.8);

    vec3 lightDir = normalize(lightPos - pos.xyz);
    vec3 viewDir = normalize(viewPos - pos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);

  //  float diff = dot(lightDir, norm) * 0.5 + 0.5;

    float diff = max(dot(norm, lightDir), 0.1);
    float spec = pow(clamp(dot(norm, reflectDir), 0.0, 1.0), specPower);

    clr = vec4((Ke + Ka +  Kd*diff) * clr.rgb  + Ks * spec, opacity * clr.a);
  }
  gl_FragColor = clr;
}

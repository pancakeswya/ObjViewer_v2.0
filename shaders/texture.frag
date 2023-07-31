#version 400 core

in vec3 pos;
in vec3 norm;
in vec2 tex;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ke;
uniform float specPower;
uniform float opacity;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D texture_a;
uniform sampler2D texture_d;
uniform sampler2D texture_s;

void main() {
  vec4 map_amb = texture2D(texture_a, tex);
  vec4 map_diff = texture2D(texture_d, tex);
  vec4 map_spec = texture2D(texture_s, tex);

  vec3 lightDir = normalize(lightPos - pos.xyz);
  if (!gl_FrontFacing) {
      lightDir = -lightDir;
  }

  vec3 viewDir = normalize(viewPos - pos.xyz);
  vec3 reflectDir = reflect(-lightDir, norm);

  float diff = max(dot(norm, lightDir), 0.0f);
  float spec = pow(max(dot(norm, reflectDir), 0.0f), specPower);

  gl_FragColor = vec4(Ke + Ka * map_amb.rgb + diff * (Kd + map_diff.rgb) +
                          Ks * spec * map_spec.rgb,
                      opacity * map_diff.a);

}

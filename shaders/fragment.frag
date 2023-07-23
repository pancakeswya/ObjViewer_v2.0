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
      vec3 lightDir = normalize(lightPos - pos.xyz);
      vec3 viewDir = normalize(viewPos - pos.xyz);
      vec3 reflectDir = reflect(-lightDir, norm);

      float diff = max(dot(norm, lightDir), 0.0f);
      float spec = pow(max(dot(norm, reflectDir), 0.0f), specPower);

      clr = vec4(Ke + Ka +  diff *(Kd + clr.rgb)  + Ks * spec, opacity * clr.a);
    }
    gl_FragColor = clr;
}

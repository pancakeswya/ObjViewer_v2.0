#version 400 core

in vec3 view_pos;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 emission;
uniform float shiness;
uniform float opacity;
uniform vec3 light_pos;
uniform sampler2D texture_a;
uniform sampler2D texture_d;
uniform sampler2D texture_s;

void main() {
  vec4 map_amb = texture2D(texture_a, tex_coords);
  vec4 map_diff = texture2D(texture_d, tex_coords);
  vec4 map_spec = texture2D(texture_s, tex_coords);

  vec3 x_tangent = dFdx(view_pos);
  vec3 y_tangent = dFdy(view_pos);

  vec3 n = normalize(cross(x_tangent, y_tangent));
  vec3 l = normalize(light_pos - view_pos);
  vec3 e = normalize(-view_pos);
  vec3 r = normalize(-reflect(l, n));

  vec3 amb = ambient * map_amb.rgb;
  vec3 diff = (diffuse + map_diff.rgb) * max(dot(n, l), 0.0f);
  diff = clamp(diff, 0.0f, 1.0f);
  vec3 spec = specular * pow(max(dot(r, e), 0.0f), shiness);
  spec = clamp(spec, 0.0f, 1.0f);

  gl_FragColor = vec4(emission + amb + diff + spec, opacity * map_diff.a);

}

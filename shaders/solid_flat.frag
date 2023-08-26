#version 400 core

in vec3 view_pos;
in vec3 normal;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 emission;
uniform float shiness;
uniform float opacity;
uniform vec3 light_pos;
uniform vec3 color;

void main() {
    vec3 x_tangent = dFdx(view_pos);
    vec3 y_tangent = dFdy(view_pos);

    vec3 n = normalize(cross(x_tangent, y_tangent));
    vec3 l = normalize(light_pos - view_pos);
    vec3 e = normalize(-view_pos);

    vec3 r = normalize(-reflect(l, n));

    vec3 diff = (diffuse + color) * max(dot(n, l), 0.0f);
    diff = clamp(diff, 0.0f, 1.0f);
    vec3 spec = specular * pow(max(dot(r, e), 0.0f), shiness);
    spec = clamp(spec, 0.0f, 1.0f);

    gl_FragColor = vec4(emission + ambient + diff + spec, opacity);
}

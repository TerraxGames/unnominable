#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec3 frag_pos;
out vec3 normal;
out vec2 texcoord;
out vec3 light_dir;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform DirectionalLight u_light;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
    frag_pos = vec3(u_view * u_model * vec4(a_pos, 1.0));
    normal = mat3(transpose(inverse(u_view * u_model))) * a_normal;
    texcoord = a_texcoord;
    light_dir = vec3(u_view * vec4(normalize(-u_light.direction), 0.0));
}

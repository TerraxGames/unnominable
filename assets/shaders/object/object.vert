#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;

out vec3 frag_pos;
out vec3 normal;
out vec2 texcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
    frag_pos = vec3(u_view * u_model * vec4(a_pos, 1.0));
    normal = vec3(transpose(inverse(u_view * u_model)) * normalize(vec4(a_normal, 0.0)));
    texcoord = a_texcoord;
}

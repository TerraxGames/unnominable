#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_face_pos;

out vec2 face_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
    face_pos = a_face_pos;
}

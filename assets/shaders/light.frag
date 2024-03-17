#version 460 core
out vec4 FragColor;

uniform vec3 u_light_color;

void main() {
    FragColor = vec4(u_light_color, 1.0);
}

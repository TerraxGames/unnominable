#version 460 core
out vec4 FragColor;

in vec3 color;

uniform float time;

void main() {
    FragColor = vec4(((sin(time / 500.0) + 1.0) / 2) * color, 1.0);
}

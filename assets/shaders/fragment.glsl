#version 460 core
out vec4 FragColor;

in vec3 color;
in vec2 texcoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    FragColor = mix(texture(texture0, texcoord), texture(texture1, texcoord), 0.2);
}

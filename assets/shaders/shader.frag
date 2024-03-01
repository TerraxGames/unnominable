#version 460 core
out vec4 FragColor;

in vec2 texcoord;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

void main() {
    FragColor = mix(texture(u_texture0, texcoord), texture(u_texture1, texcoord), 0.2);
}

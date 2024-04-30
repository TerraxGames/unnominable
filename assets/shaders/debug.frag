#version 460 core
out vec4 FragColor;

in vec2 face_pos;

void main() {
    FragColor = vec4(face_pos.x, 0.0, face_pos.y, 1.0);
}

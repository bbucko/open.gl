#version 330 core

in vec2 position;
in vec3 color;

out vec3 Color;

void main(void) {
    Color = vec3(color);
    gl_Position = vec4(-position.x, -position.y, 0.0, 1.0);
}
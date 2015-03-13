#version 330 core

in vec3 Color;

out vec4 outColor;

void main(void) {
    outColor = vec4(1-Color.r, 1-Color.g, 1-Color.b, 1.0);
}
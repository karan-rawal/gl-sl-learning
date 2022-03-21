#version 330 core

uniform float colorMultiplier;

in vec3 color;

out vec4 FragColor;

void main() {
    FragColor = vec4(color * colorMultiplier, 1.0f);
}
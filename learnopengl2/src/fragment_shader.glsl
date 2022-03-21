#version 330 core

uniform float colorMultiplier;
uniform sampler2D textureSampler2D;

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

void main() {
    FragColor = mix(vec4(color, 1.0f), texture(textureSampler2D, texCoord), colorMultiplier);
}
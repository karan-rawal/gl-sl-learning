#version 330 core

in vec2 voTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec4 oFragColor;

void main() {
    oFragColor = mix(texture(uTexture1, voTexCoord), texture(uTexture2, voTexCoord), 0.5f);
}
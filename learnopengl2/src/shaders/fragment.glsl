#version 330 core

in vec3 voColor;
in vec2 voTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec4 oFragColor;

void main() {
    vec4 mix1 = mix(texture(uTexture1, voTexCoord), texture(uTexture2, voTexCoord), 0.9f);
    oFragColor = mix(vec4(voColor, 1.0f), mix1, 0.5f);
}
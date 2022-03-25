#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 voColor;
out vec2 voTexCoord;

void main() {
    voColor = aColor;
    voTexCoord = aTexCoord;
    gl_Position = vec4(aPosition, 1.0f);
}
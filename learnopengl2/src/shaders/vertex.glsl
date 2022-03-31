#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uMVP;

out vec2 voTexCoord;

void main() {
    voTexCoord = aTexCoord;
    gl_Position = uMVP * vec4(aPosition, 1.0f);
}
#version 410 core

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec2 vertexUv;

layout(location = 0) out vec2 uv;

void main() {
    gl_Position = vec4(vertexPos.x, vertexPos.y, 0, 1);
    uv = vertexUv;
}

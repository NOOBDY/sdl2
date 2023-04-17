#version 410 core

layout(location = 0) in vec2 uv;

uniform sampler2D text;

layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = texture(text, uv);
    // fragColor = vec4(1.0);
}

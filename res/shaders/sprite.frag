#version 330 core

out vec4 oColor;

in vec2 vUv;

uniform sampler2D textureSampler;

void main() {
    oColor = texture2D(textureSampler, vUv);
}
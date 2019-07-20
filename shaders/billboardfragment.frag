#version 330 core

in vec2 UV;

uniform sampler2D TextureSampler;

out vec4 FragColor;

void main() {
    FragColor = texture(TextureSampler, UV);
}

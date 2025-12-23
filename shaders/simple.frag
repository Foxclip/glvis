#version 330 core

in vec2 TexCoords;
in vec4 Color;

out vec4 FragColor;

uniform sampler2D tex;
uniform bool hasTexture;
  
void main() {
    if (hasTexture) {
        FragColor = texture(tex, TexCoords) * Color;
    } else {
        FragColor = Color;
    }
}

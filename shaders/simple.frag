#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;
uniform bool hasTexture;
  
void main() {
    if (hasTexture) {
        FragColor = texture(tex, TexCoords);
    } else {
        FragColor = vec4(color);
    }
}

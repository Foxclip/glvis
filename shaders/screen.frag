#version 330 core
out vec4 FragColor;
  
in vec4 Color;
in vec2 TexCoords;

uniform sampler2D tex;

void main() { 
    FragColor = texture(tex, TexCoords) * Color;
}

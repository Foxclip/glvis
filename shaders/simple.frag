#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;
uniform bool hasTexture;
  
void main() {
    if (hasTexture) {
        FragColor = texture(tex, gl_FragCoord.xy);
    } else {
        FragColor = vec4(color);
    }
}

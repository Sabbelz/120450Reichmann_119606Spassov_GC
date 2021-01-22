#version 150

in vec3 TextDir;

out vec4 FragColour;

uniform samplerCube skybox;

void main() {
    FragColour = texture(skybox, TextDir);
}

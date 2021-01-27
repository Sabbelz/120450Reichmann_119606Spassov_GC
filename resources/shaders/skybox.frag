#version 150

in vec3 TextDir;

out vec4 FragColour;

uniform samplerCube Skybox;

void main() {
    FragColour = texture(Skybox, TextDir);
}

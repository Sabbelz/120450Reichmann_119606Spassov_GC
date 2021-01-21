#version 150

in vec3 pos;

out vec3 TextDir;

uniform mat4 ProjectionMatrix, ViewMatrix;

void main() {
    TextDir = pos;
    mat4 vm = mat4(mat3(ViewMatrix));
    gl_Position = ProjectionMatrix * vm * vec4(pos, 1.0);
}

#version 150

#extension GL_ARB_explicit_attrib_loaction : require

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec2 in_texture_coordinates;

out pass_tex_coordinates;

void main() {
    gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
    pass_tex_coordinates = in_texture_coordinates;
}
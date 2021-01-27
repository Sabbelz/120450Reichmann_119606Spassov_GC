#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_texture_coordinates;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix, ViewMatrix, ProjectionMatrix, NormalMatrix;

out vec2 pass_tex_coordinates;
out vec3 pass_Normal, pass_Position, pass_Camera_Position;
out mat4 pass_model_matrix, pass_view_matrix, pass_normal_matrix;

void main(void)
{
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);
	pass_Normal = (NormalMatrix * vec4(in_Normal, 0.0)).xyz;
	pass_Position = ((ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0)).xyz;
	pass_Camera_Position = (ViewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	pass_tex_coordinates = in_texture_coordinates;
	pass_model_matrix = ModelMatrix;
	pass_view_matrix = ViewMatrix;
	//pass_normal_matrix = NormalMatrix;
}

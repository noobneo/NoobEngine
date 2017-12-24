#version 330 core

layout (location = 0) in vec3 position;
layout (location = 0) in vec3 color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix  = mat4(1.0);
uniform mat4 modeling_matrix;

out vec3 out_color;

void main() 
{
	vec4  pos = vec4(position,1.0);
	gl_Position =  projection_matrix*view_matrix*modeling_matrix*pos;
	out_color = color;
}
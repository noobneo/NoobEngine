#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texturecoords;

uniform mat4 projection_matrix;
uniform mat4 view_matrix  = mat4(1.0);
uniform mat4 modeling_matrix;

//sprite frame related
uniform int frame_index = 0;
uniform float texture_width_  = 1.0;

out vec3 ourColor;
out vec2 TexCoord;

//testing
uniform float rect_x = 1.0;

void main() 
{
	vec4  pos = vec4(position,1.0);
	//gl_Position =  pos;
	gl_Position = projection_matrix*view_matrix*modeling_matrix*pos;

	//new_x = texture_x +(frame_rect_x*texture_width*frame_index)

	TexCoord.x = texturecoords.x+rect_x*texture_width_*frame_index;//sprite animation
	TexCoord.y = texturecoords.y;
	ourColor = color;
}
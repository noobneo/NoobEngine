#version 330 core

out vec4 frag_color;
in vec3 out_color;
uniform vec4 color;

void main()
{
	frag_color = vec4(color.r, color.g,color.b, color.a);
}
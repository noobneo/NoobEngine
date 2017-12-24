#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform float alpha;

void main()
{
	vec4 c= texture(texture1, TexCoord); 
	c.a *= alpha;
	c.r*=ourColor.r;
	FragColor = c;
}
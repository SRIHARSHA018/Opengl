#version 460 core

in vec4 vColor;
layout(location = 0) out vec4 color;
uniform vec4 uColor;
uniform bool shader;

void main()
{
	if (shader)
	{
		color =uColor;
	}
	else
	{
		color = vColor;
	}
}
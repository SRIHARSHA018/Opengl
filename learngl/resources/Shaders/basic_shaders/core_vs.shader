#version 460 core

out vec4 vColor;

layout(location = 0) in vec4 position;

void main()
{
	gl_Position =position;
	vColor = vec4(clamp(position,0.f,1.f));
}
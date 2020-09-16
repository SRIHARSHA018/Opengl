#version 460 core

out vec4 vColor;


layout(location = 0) in vec4 position;
uniform mat4 u_model;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection*u_View*u_model*position;
	vColor = vec4(clamp(position,0.f,1.f));
}
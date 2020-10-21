#version 460 core
layout(location = 0) in vec3 vertex_Position;

uniform mat4 u_model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
	gl_Position = u_Projection * u_View * u_model * vec4(vertex_Position, 1.0f);
}
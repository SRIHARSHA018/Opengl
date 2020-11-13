#version 460 core

//layouts
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;

//uniforms
uniform mat4 u_model;
uniform mat4 u_Projection;
uniform mat4 u_View;

//outs
out vec3 v_normal;
out vec2 v_texcoord;
out vec3 frag_pos;
 
//main
void main()
{
	//camera pos
	frag_pos = vec4(u_model *vec4(vertex_position,1.f)).xyz;
	gl_Position = u_Projection*	u_View*u_model*vec4(vertex_position,1.f);
	//texture coords
	v_texcoord = vertex_texcoord;
	//normals
	v_normal = (transpose(inverse(u_model)) * vec4(vertex_normal, 0.f)).xyz;
}
#version 460 core

in vec4 vColor;
in vec2 v_texcoord;
layout(location = 0) out vec4 color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texcolor = texture(u_Texture, v_texcoord);
	color = texcolor*vColor;
}
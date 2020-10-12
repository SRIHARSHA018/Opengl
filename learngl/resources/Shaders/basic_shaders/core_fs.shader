#version 460 core

in vec4 vColor;
in vec2 v_texcoord;
layout(location = 0) out vec4 color;
uniform vec4 uColor;
uniform bool shader;
uniform sampler2D u_Texture;

void main()
{
	if (shader)
	{
		vec4 texcolor = texture(u_Texture, v_texcoord);
		color = texcolor;
	}
	else
	{
		color = vColor;
	}
}
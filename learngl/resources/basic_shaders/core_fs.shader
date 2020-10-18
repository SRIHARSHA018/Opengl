#version 460 core

//structure for phonglighting model
struct DirectionalLight
{
	vec3 Lightcolor;
	float a_intensity;
};

//in's
in vec2 v_texcoord;
in vec3 v_normal;
in vec3 frag_pos;

//layouts
layout(location = 0) out vec4 frag_color;

//uniforms
uniform DirectionalLight u_directional_light;
uniform sampler2D u_Texture;
uniform vec3 u_cameraPos;

void main()
{
	//ambient light
	vec3 ambient = u_directional_light.Lightcolor* u_directional_light.a_intensity;
	//diffuse
	//texture
	vec4 texcolor = texture(u_Texture, v_texcoord);
	//specular
	//output
	frag_color = texcolor*vec4(ambient,1.0f);
	
}
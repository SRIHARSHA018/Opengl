#version 460 core

//structure for phonglighting model
struct DirectionalLight
{
	float a_intensity;
	float DiffuseIntensity;
	float SpecularIntensity;
	float SpecularPower;
	vec3 LightColor;
	vec3 DiffuseDirection;

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
	vec4 ambient = vec4(u_directional_light.LightColor* u_directional_light.a_intensity,1.0f);
	//diffuse
	vec3 lightDir = normalize(u_directional_light.DiffuseDirection - frag_pos);
	float diffuse_factor = max(dot(normalize(v_normal), lightDir), 0.f);
	vec4 diffuse = vec4(u_directional_light.LightColor * u_directional_light.DiffuseIntensity * diffuse_factor, 1.0f);
	//specular
	vec3 V = normalize(u_cameraPos-frag_pos);
	vec3 R = normalize(reflect(-u_directional_light.DiffuseDirection, v_normal));
	float specular_factor = max(dot(V, R),0.f);
	specular_factor = pow(specular_factor, u_directional_light.SpecularPower);
	vec4 specular = vec4(u_directional_light.LightColor * u_directional_light.SpecularIntensity * specular_factor, 1.0f);
	//texture
	vec4 texcolor = texture(u_Texture, v_texcoord);
	//output
	vec3 objectColor = vec3(1.0, 0.3, 0.2);
	frag_color = texcolor*(ambient+diffuse+specular);
	
}
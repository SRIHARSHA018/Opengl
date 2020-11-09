#version 460 core

//structure for phonglighting model
struct Material
{

	sampler2D diffuse;
	sampler2D specular;
	float     specular_strength;
	float     specular_intensity;
};

struct DirectionalLight
{
	vec3 DiffuseDirection;
	float ambient_intensity;
	float DiffuseIntensity;
	vec3 LightColor;
};
struct PointLight
{
	vec3 PointLightPosition;
	float ambient_intensity;
	float DiffuseIntensity;
	vec3 LightColor;

	float quadratic;
	float linearv;
	float constant;
};

//in's
in vec2 v_texcoord;
in vec3 v_normal;
in vec3 frag_pos;

//layouts
layout(location = 0) out vec4 frag_color;

//uniforms
uniform PointLight u_point_light;
uniform DirectionalLight u_directional_light;
uniform Material u_material;
uniform vec3 u_cameraPos;

//Directional Light Calculation
vec4 CalDirectionalLight(DirectionalLight light, Material material, vec3 normal,vec2 texturecoords)
{
	vec3 lightDir = normalize(light.DiffuseDirection);

	//ambient light
	vec4 ambient = vec4(light.LightColor * light.ambient_intensity*vec3(texture(material.diffuse, texturecoords)), 1.0f);
	
	//diffuse
	float diffuse_factor = max(dot(normalize(normal), lightDir), 0.f);
	vec4 diffuse = vec4(light.LightColor *light.DiffuseIntensity * diffuse_factor* vec3(texture(material.diffuse, texturecoords)),1.0f);
	
	//specular
	vec3 V = normalize(u_cameraPos - frag_pos);
	vec3 R = normalize(reflect(-light.DiffuseDirection, normal));
	float specular_factor = max(dot(V, R), 0.f);
	specular_factor = pow(specular_factor,material.specular_strength);
	vec4 specular = vec4(light.LightColor *material.specular_intensity * specular_factor, 1.0f);

	return ambient + diffuse + specular;
}

vec4 CalPointLight(PointLight light, Material material, vec3 normal, vec2 texturecoords)
{
	vec3 lightDir = normalize(light.PointLightPosition - frag_pos);
	
	//ambient
	vec3 ambient = light.LightColor * light.ambient_intensity * vec3(texture(material.diffuse, texturecoords));
	
	//diffuse
	float diffuse_factor = max(dot(normalize(normal), lightDir), 0.f);
	vec3 diffuse = light.LightColor * diffuse_factor * light.DiffuseIntensity * vec3(texture(material.diffuse, texturecoords));
	
	//specular
	vec3 V = normalize(u_cameraPos - frag_pos);
	vec3 R = reflect(-lightDir, normalize(normal));
	float specular_factor = pow(max(dot(V, R), 0.f),material.specular_strength);
	vec3 specular = light.LightColor * specular_factor * material.specular_intensity;

	//attenuation
	float distance = length(light.PointLightPosition-frag_pos);
	float attenuation = 1.f / (light.quadratic * distance * distance + light.linearv * distance + light.constant);
	ambient *= attenuation;
	specular *= attenuation;
	diffuse *= attenuation;
	return vec4(ambient+diffuse+specular,1.0f);
}


void main()
{

	//output
	vec4 result = CalDirectionalLight(u_directional_light, u_material, v_normal, v_texcoord);

	result += CalPointLight(u_point_light, u_material, v_normal, v_texcoord);
	frag_color = result;

}
#version 460 core
#define Max_Point_Lights 10
#define Max_Spot_Lights 10
#define Standard_mat 0
#define base_mat 1


struct BaseMaterial
{
	sampler2D diffuse;
	sampler2D specular;
	float     specular_strength;
};

struct StandardMaterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Material
{
	StandardMaterial standard;
	BaseMaterial base;
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
struct SpotLight
{
	
	vec3 direction;
	vec3 SpotLightPosition;
	float cutoff;
	float OuterCutOff;
	PointLight base;	
};
//in's
in vec2 v_texcoord;
in vec3 v_normal;
in vec3 frag_pos;



//uniforms======================================

	//lights
	uniform PointLight u_point_light[Max_Point_Lights];
	uniform SpotLight u_spot_light[Max_Spot_Lights];
	uniform DirectionalLight u_directional_light;

	//parameters
	uniform vec3 u_cameraPos;
	uniform int u_no_spot_lights;
	uniform int u_no_point_lights;
	uniform float u_Dir_intensity;

	//material
	uniform int type;
	uniform Material u_material;

//Directional Light Calculation===========================
vec4 CalDirectionalLight(DirectionalLight light, Material material, vec3 normal,vec2 texturecoords)
{
	vec3 lightDir = normalize(light.DiffuseDirection);
	float diffuse_factor = max(dot(normalize(normal), lightDir), 0.f);
	vec3 V = normalize(u_cameraPos - frag_pos);
	vec3 R = normalize(reflect(-light.DiffuseDirection, normal));
	float specular_factor = max(dot(V, R), 0.f);
	if(type==Standard_mat)
	{
		vec4 ambient = vec4(light.LightColor * light.ambient_intensity * material.standard.ambient , 1.0f);
		vec4 diffuse = vec4(light.LightColor *light.DiffuseIntensity * diffuse_factor* material.standard.diffuse,1.0f);
		specular_factor = pow(specular_factor,material.standard.shininess);
		vec4 specular = vec4(light.LightColor * specular_factor*material.standard.specular, 1.0f);
		return ambient + diffuse + specular;
	}
	else
	{
		vec4 ambient = vec4(light.LightColor * light.ambient_intensity*vec3(texture(material.base.diffuse, texturecoords)), 1.0f);
		vec4 diffuse = vec4(light.LightColor *light.DiffuseIntensity * diffuse_factor* vec3(texture(material.base.diffuse, texturecoords)),1.0f);
		specular_factor = pow(specular_factor,material.base.specular_strength);
		vec4 specular = vec4(light.LightColor * specular_factor*vec3(texture(material.base.specular,texturecoords)), 1.0f);
		return ambient + diffuse + specular;
	}


}
//point light cal===================================
vec4 CalPointLight(PointLight light, Material material, vec3 normal, vec2 texturecoords)
{
	vec3 lightDir = normalize(light.PointLightPosition - frag_pos);
	vec3 V = normalize(u_cameraPos - frag_pos);
	vec3 R = reflect(-lightDir, normal);
	float distance = length(light.PointLightPosition-frag_pos);
	float attenuation = 1.f / (light.quadratic * distance * distance + light.linearv * distance + light.constant);
	if(type==Standard_mat)
	{
		float diffuse_factor = max(dot(normal, lightDir),0.f);
		vec3 ambient = light.LightColor * light.ambient_intensity *material.standard.ambient;
		vec3 diffuse = light.LightColor * diffuse_factor * light.DiffuseIntensity *material.standard.diffuse;
		float specular_factor = pow(max(dot(V, R), 0.f),material.standard.shininess);
		vec3 specular = (light.LightColor * specular_factor*material.standard.specular);

		ambient *= attenuation;
		specular *= attenuation;
		diffuse *= attenuation;
		return vec4(ambient+diffuse+specular,1.0f);
		
	}
	else
	{
		
		float diffuse_factor = max(dot(normalize(normal), lightDir),0.f);
		vec3 ambient = light.LightColor * light.ambient_intensity * vec3(texture(material.base.diffuse, texturecoords));
		vec3 diffuse = light.LightColor * diffuse_factor * light.DiffuseIntensity * vec3(texture(material.base.diffuse, texturecoords));
		float specular_factor = pow(max(dot(V, R), 0.f),material.base.specular_strength);
		vec3 specular = (light.LightColor * specular_factor*vec3(texture(material.base.specular,texturecoords)));
		ambient *= attenuation;
		specular *= attenuation;
		diffuse *= attenuation;
		return vec4(ambient+diffuse+specular,1.0f);
	}

	
}
//SpotLight ==============================================
vec4 CalSpotLight(SpotLight light, Material material, vec3 normal, vec2 texturecoords)
{
	vec3 lightDir = normalize(light.SpotLightPosition - frag_pos);
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutoff-light.OuterCutOff;
	float intensity =clamp((theta-light.OuterCutOff)/epsilon,0.f,1.f);
	vec3 V = normalize(u_cameraPos - frag_pos);
	vec3 R = reflect(-lightDir, normalize(normal));
	float distance = length(light.SpotLightPosition-frag_pos);
	float attenuation = 1.f / (light.base.quadratic * distance * distance + light.base.linearv * distance + light.base.constant);
	if(type==Standard_mat)
	{
		float diffuse_factor = max(dot(normal, lightDir), 0.f);
		vec3 ambient = light.base.LightColor * light.base.ambient_intensity * material.standard.ambient;
		vec3 diffuse = light.base.LightColor * diffuse_factor * light.base.DiffuseIntensity *material.standard.diffuse;
		float specular_factor = pow(max(dot(V, R), 0.f),material.standard.shininess);
		vec3 specular = (light.base.LightColor * specular_factor*material.standard.specular);

		diffuse *=intensity;
		specular*=intensity;
		ambient *= attenuation;
		specular *= attenuation;
		diffuse *= attenuation;
		return vec4(max(ambient+diffuse+specular,ambient),1.0f);
	}
	else
	{
		float diffuse_factor = max(dot(normalize(normal), lightDir), 0.f);
		vec3 ambient = light.base.LightColor * light.base.ambient_intensity * vec3(texture(material.base.diffuse, texturecoords));
		vec3 diffuse = light.base.LightColor * diffuse_factor * light.base.DiffuseIntensity * vec3(texture(material.base.diffuse, texturecoords));
		float specular_factor = pow(max(dot(V, R), 0.f),material.base.specular_strength);
		vec3 specular = (light.base.LightColor * specular_factor*vec3(texture(material.base.specular,texturecoords)));
		diffuse *=intensity;
		specular*=intensity;
		ambient *= attenuation;
		specular *= attenuation;
		diffuse *= attenuation;
		return vec4(ambient+diffuse+specular,1.0f);
	}

	
}

//main=======================
void main()
{
	
	vec4 result= vec4(0.f);
	//output
	result = CalDirectionalLight(u_directional_light, u_material, v_normal, v_texcoord)*u_Dir_intensity;
	for(int i=0;i<(u_no_point_lights);i++)
	{
		result+= CalPointLight(u_point_light[i],u_material,v_normal,v_texcoord);
	}
	for(int i=0;i<(u_no_spot_lights);i++)
	{
		result+=CalSpotLight(u_spot_light[i],u_material,v_normal,v_texcoord);
	}

	gl_FragColor =result;

}

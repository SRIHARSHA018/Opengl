#include "Light.h"

Light::Light()
{
	x_AmbientIntensity = 1.f;
	x_DiffuseIntensity = 0.f;
	x_Color = glm::vec3(1.f);
	x_DiffuseDirection = glm::vec3(0.f);

}

Light::Light(float ambientintensity,float red,float green,float blue,
	float diffintensity, glm::vec3 diffusedirection,float specular_intensity,float specular_pow)
{
	//ambient
	x_AmbientIntensity = ambientintensity;
	x_Color = glm::vec3(red,green,blue);
	//diffuse
	x_DiffuseIntensity = diffintensity;
	x_DiffuseDirection = diffusedirection;
	//specular
	x_specularpow = specular_pow;
	x_SpecularIntensity = specular_intensity;
}

Light::~Light()
{

}

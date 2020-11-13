#include "Light.h"

Light::Light()
{
	x_AmbientIntensity = 1.f;
	x_DiffuseIntensity = 1.f;
	x_Color = glm::vec3(1.f);
	
}

Light::Light(float ambientintensity, float red, float green, float blue,
	float diffintensity)
{
	//ambient
	x_AmbientIntensity = ambientintensity;
	x_Color = glm::vec3(red, green, blue);
	//diffuse
	x_DiffuseIntensity = diffintensity;
}

Light::~Light()
{

}

void Light::SetLightColor(glm::vec3& color)
{
	x_Color = color;
}





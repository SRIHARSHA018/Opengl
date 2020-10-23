#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(float ambientintensity, float red, float green, float blue,
	float diffintensity, glm::vec3 position, float specular_intensity, float specular_pow)
{
	x_Position = position;
}

void PointLight::SetPointLightPos(float x, float y, float z)
{
	x_Position.x = x;
	x_Position.y = y;
	x_Position.z = z;
}

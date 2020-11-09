#include "PointLight.h"

PointLight::PointLight()
	:Light()
{
	x_Position = glm::vec3(0.f, 0.f, 0.f);
}

PointLight::PointLight(float ambientintensity,
	float red, float green, float blue,
	float diffintensity)
	:Light(ambientintensity,red,green,blue,diffintensity)
{

	x_Position = glm::vec3(0.f, 1.f, 1.f);

}

void PointLight::SetAttenuationParameters(float a, float b, float c)
{
	this->x_constant = c;
	this->x_linear = b;
	this->x_quadratic = a;
}


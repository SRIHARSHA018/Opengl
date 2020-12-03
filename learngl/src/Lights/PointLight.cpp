#include "PointLight.h"
int PointLight::x_light_count = 0;



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

void PointLight::CreatePointLights(int& count)
{	
	for (int i = 0; i < count; i++)
	{

		pointLights.push_back(PointLight(0.1f, 1.f, 1.f, 1.f, 1.0f));
		pointLights[i].SetAttenuationParameters(0.032f, 0.09f, 1.0f);
		x_light_count+=1;		
	}
	
}

void PointLight::SetPointLightUIcontroller( std::vector<glm::vec3>& color, std::vector<glm::vec3>& position,int& count)
{
	for (int i = 0; i < count; i++)
	{
		pointLights[i].SetLightColor(color[i]);
		pointLights[i].SetPointLightPos(position[i]);
	}

}


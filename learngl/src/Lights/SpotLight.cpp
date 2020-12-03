#include "SpotLight.h"
int SpotLight::x_light_count = 0;

SpotLight::SpotLight()
	:Light()
{
	x_Position = glm::vec3(0.f, 0.f, 0.f);
	x_direction = glm::vec3(0.f, 1.f, 0.f);
	x_cutOff = glm::cos(glm::radians(12.5f));
}

SpotLight::SpotLight(float ambientintensity,
	float red, float green, float blue,
	float diffintensity)
	:Light(ambientintensity,red,green,blue,diffintensity)
{
	x_Position = glm::vec3(0.f, 1.f, 1.f);
	x_direction = glm::vec3(0.f, 1.f, 0.f);

}

void SpotLight::SetAttenuationParameters(float a, float b, float c)
{
	this->x_constant = c;
	this->x_linear = b;
	this->x_quadratic = a;
}

void SpotLight::CreateSpotLights(int& count)
{
	
	
	for (int i = 0; i < count; i++)
	{
		SpotLights.push_back(SpotLight(0.1f, 1.f, 1.f, 1.f, 1.0f));
		SpotLights[i].SetAttenuationParameters(0.032f, 0.09f, 1.0f);
		x_light_count+=1;		
	}
	

	
}

void SpotLight::SetSpotLightUIcontroller( std::vector<glm::vec3>& color, std::vector<glm::vec3>& position,
	std::vector<glm::vec3>& direction,std::vector <float>& cutOff,
	std::vector<float>&OuterCutOff,
	int& count)
{
	for (int i = 0; i < count; i++)
	{
		SpotLights[i].SetLightColor(color[i]);
		SpotLights[i].SetSpotLightPos(position[i]);
		SpotLights[i].SetSpotLightDir(direction[i]);
		SpotLights[i].SetSpotLightCutOff(cutOff[i]);
		SpotLights[i].SetSpotLightOuterCutOff(OuterCutOff[i]);
	}
}


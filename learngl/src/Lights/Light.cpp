#include "Light.h"

Light::Light()
{
	x_AmbientIntensity = 1.f;
	x_Color = glm::vec3(1.f);
}

Light::Light(float ambientintensity,float red,float green,float blue)
{
	//ambient
	x_AmbientIntensity = ambientintensity;
	x_Color = glm::vec3(red,green,blue);
}

Light::~Light()
{

}

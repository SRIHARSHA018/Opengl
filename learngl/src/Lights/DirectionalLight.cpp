#include "DirectionalLight.h"

DirectionalLight::DirectionalLight():Light()
{
	x_LightDirection = glm::vec3(0.f, 1.f, 0.f);
}

DirectionalLight::DirectionalLight(float ambientintensity, float red, float green, float blue,
	float diffintensity, glm::vec3 diffusedirection)
	:Light(ambientintensity,red,green,blue,diffintensity)
{
	x_LightDirection = diffusedirection;

}
void DirectionalLight::SetLightDirection(float x, float y, float z)
{
	x_LightDirection.x = x;
	x_LightDirection.y = y;
	x_LightDirection.z = z;
}

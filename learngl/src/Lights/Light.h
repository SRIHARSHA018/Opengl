#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
class Light
{
public:
	Light();
	Light(float ambientintensity, float red, float green, float blue);
	float GetAmbientIntensity() { return x_AmbientIntensity; }
	glm::vec3 GetLightColor() { return x_Color; }
	~Light();
private:
	float x_AmbientIntensity;
	glm::vec3 x_Color;
};


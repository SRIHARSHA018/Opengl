#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>

class Light
{
public:
	Light();
	Light(float ambientintensity, float red, float green, float blue,
		float diffintensity);
	~Light();
	float GetAmbientIntensity() const { return x_AmbientIntensity; }
	float GetDiffuseIntensity()const { return x_DiffuseIntensity; }
	glm::vec3 GetLightColor()const { return x_Color; }
	void SetLightColor(glm::vec3& color);
private:
	float x_AmbientIntensity;
	float x_DiffuseIntensity;
	glm::vec3 x_Color;
};


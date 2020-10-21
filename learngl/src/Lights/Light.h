#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
class Light
{
public:
	Light();
	Light(float ambientintensity, float red, float green, float blue,
		float diffintensity,glm::vec3 diffusedirection,float specintensity,float spepcular_pow);
	~Light();
	float GetSpecularIntensity() { return x_SpecularIntensity; }
	float GetSpecularPower() { return x_specularpow; }
	float GetAmbientIntensity() { return x_AmbientIntensity; }
	float GetDiffuseIntensity() { return x_DiffuseIntensity; }
	glm::vec3 GetLightColor() { return x_Color; }
	glm::vec3 GetDiffuseDirection() { return x_DiffuseDirection; }
	void SetLightPos(float x, float y,float z);
private:
	
	float x_AmbientIntensity;
	float x_DiffuseIntensity;
	float x_specularpow;
	float x_SpecularIntensity;
	glm::vec3 x_Color;
	glm::vec3 x_DiffuseDirection;
};


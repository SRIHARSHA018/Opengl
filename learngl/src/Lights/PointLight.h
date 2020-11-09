#pragma once
#include"Light.h"
class PointLight :public Light
{
private:
	glm::vec3 x_Position;
	float x_quadratic;
	float x_linear;
	float x_constant;

public:
	PointLight();
	PointLight(float ambientintensity, float red, float green, float blue,
		float diffintensity);
	glm::vec3 GetPointLightPos() { return x_Position; }
	void SetPointLightPos(const glm::vec3& position) { x_Position = position; }
	void SetAttenuationParameters(float a, float b, float c);
	float GetAttenuationConstant() { return x_constant; }
	float GetAttenuationLinear() { return x_linear; }
	float GetAttenuationQuadratic() { return x_quadratic; }
};


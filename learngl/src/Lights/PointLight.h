#pragma once
#include"Light.h"
#include<iostream>
#include<vector>
class PointLight :public Light
{
private:
	glm::vec3 x_Position;
	float x_quadratic;
	float x_linear;
	float x_constant;
	static int x_light_count;
public:
	std::vector<PointLight> pointLights;
	PointLight();
	PointLight(float ambientintensity, float red, float green, float blue,
		float diffintensity);
	glm::vec3 GetPointLightPos()const { return x_Position; }
	void SetPointLightPos(const glm::vec3& position) { x_Position = position; }
	void SetAttenuationParameters(float a, float b, float c);
	float GetAttenuationConstant()const { return x_constant; }
	float GetAttenuationLinear()const { return x_linear; }
	float GetAttenuationQuadratic()const { return x_quadratic; }
	void CreatePointLights(int& count);
	int GetLightsCount()const { return x_light_count; }
	void SetPointLightUIcontroller( std::vector<glm::vec3> &color, std::vector<glm::vec3>&position,int& count);
};


#pragma once
#include"Light.h"
#include<iostream>
#include<vector>
class SpotLight :public Light
{
private:
	glm::vec3 x_Position;
	glm::vec3 x_direction;
	float x_cutOff;
	float x_OuterCutOff;
	float x_quadratic;
	float x_linear;
	float x_constant;
	static int x_light_count;
public:
	std::vector<SpotLight> SpotLights;
	SpotLight();
	SpotLight(float ambientintensity, float red, float green, float blue,
		float diffintensity);
	glm::vec3 GetSpotLightPos()const { return x_Position; }
	glm::vec3 GetSpotLightDir()const { return x_direction; }
	float GetSpotLightCutOff()const { return x_cutOff; }
	float GetSpotLightOuterCutOff()const { return x_OuterCutOff; }
	void SetSpotLightPos(const glm::vec3& position) { x_Position = position; }
	void SetSpotLightDir(const glm::vec3& direction) { x_direction = direction; }
	void SetSpotLightCutOff(const float& cutoff) { x_cutOff = cutoff; }
	void SetSpotLightOuterCutOff(const float& OuterCutoff) { x_OuterCutOff = OuterCutoff; }
	void SetAttenuationParameters(float a, float b, float c);
	float GetAttenuationConstant()const { return x_constant; }
	float GetAttenuationLinear()const { return x_linear; }
	float GetAttenuationQuadratic()const { return x_quadratic; }
	int GetLightsCount()const { return x_light_count; }
	void CreateSpotLights(int& count);
	void SetSpotLightUIcontroller( std::vector<glm::vec3> &color, std::vector<glm::vec3>&position,
		std::vector<glm::vec3>& direction,
		std::vector <float>& cutOff,
		std::vector<float>& OuterCutOff,
		int& count);
};


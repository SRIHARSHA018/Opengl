#pragma once
#include "Material.h"

class BasicMaterial :public Material
{
private:
	unsigned int x_diffuse_tex;
	unsigned int x_specular_tex;
	float     x_specular_power;
	unsigned int x_slot = 0;

public:

	BasicMaterial();
	BasicMaterial(unsigned int diffuse,unsigned int specular, float specular_power);
	~BasicMaterial(){}
	unsigned int GetDiffuseTexture() { return x_diffuse_tex; }
	unsigned int GetSpecularTexture() { return x_specular_tex; }
	float GetspecularPower() { return x_specular_power; }
	int GetMaterialType(){ return this->Materialtype; }
};


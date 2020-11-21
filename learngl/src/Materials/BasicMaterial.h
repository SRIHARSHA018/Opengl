#pragma once
#include "Material.h"
class BasicMaterial :public Material
{
private:
	unsigned int x_diffuse_tex;
	unsigned int x_specular_tex;
	float     x_specular_power;

public:
	BasicMaterial(unsigned int diffuse,unsigned int specular, float specular_power);
	void AssignMaterial(SJ_engine::SJ_shader::shader* obj) override;
	~BasicMaterial(){}
};


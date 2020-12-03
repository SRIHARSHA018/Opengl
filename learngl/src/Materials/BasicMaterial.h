#pragma once
#include "Material.h"
#include <unordered_map>
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
	void AssignMaterial(SJ_engine::SJ_shader::shader* obj) override;
	~BasicMaterial(){}
};


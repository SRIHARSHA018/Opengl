#pragma once
#include"Material.h"

class StandardMaterial :public Material
{

public:
	enum Materials {
		emerald,
		jade,
		obsidian,
		pearl,
		ruby,
		turquoise,
		brass,
		bronze,
		chrome,
		copper,
		gold,
		silver,
		plastic,
		rubber
	};
	void SetMaterialName(Materials name);
	void AssignMaterial(SJ_engine::SJ_shader::shader* obj) override;
	StandardMaterial(Materials name);
	StandardMaterial(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, float shininess);
	~StandardMaterial() {}
private:

	glm::vec3 x_diffuse;
	glm::vec3 x_ambient;
	glm::vec3 x_specular;
	float x_shininess;
	Materials x_name;
};
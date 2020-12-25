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
	StandardMaterial(Materials name);
	StandardMaterial(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, float shininess);
	~StandardMaterial() {}
	void SetMaterialName(Materials name);
private:

	glm::vec3 x_diffuse;
	glm::vec3 x_ambient;
	glm::vec3 x_specular;
	float x_shininess;
	Materials x_name;
public:
	glm::vec3 GetDiffuse() { return x_diffuse; }
	glm::vec3 GetAmbient() { return x_ambient; }
	glm::vec3 GetSpecular() { return x_specular; }
	float GetSpecularPower () { return x_shininess; }
	int GetMaterialType() { return this->Materialtype; }

};
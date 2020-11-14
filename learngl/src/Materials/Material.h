#pragma once

#include<GL/glew.h>
#include"src/Shaders/shader.h"

class Material
{
private:
	glm::vec3 x_diffuse;
	glm::vec3 x_ambient;
	unsigned int x_diffuse_tex;
	unsigned int x_specular_tex;
	float     x_specular_intensity;
	float     x_specular_power;

public:

	Material(unsigned int diffuse,
		float specular_power,
		unsigned int specular);
	~Material(){}
	void AssignMaterial(SJ_engine::SJ_shader::shader* obj);
};


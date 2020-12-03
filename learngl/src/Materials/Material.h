#pragma once

#include<GL/glew.h>
#include<memory>
#include"src/Shaders/shader.h"
#include"src/Materials/textures/texture.h"

class Material :public Texture
{
public:
	enum samplerType {
		Diffuse,
		Specular,
		SpecularStrength
	};
	Material(){}
	~Material() {}
	int Materialtype = -1;
	virtual void AssignMaterial(SJ_engine::SJ_shader::shader* obj)= 0;
	
};


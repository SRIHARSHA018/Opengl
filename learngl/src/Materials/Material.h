#pragma once

#include<GL/glew.h>
#include"src/Shaders/shader.h"

class Material
{
public:
	int Materialtype = -1;

	~Material() {}
	virtual void AssignMaterial(SJ_engine::SJ_shader::shader* obj)= 0;
};


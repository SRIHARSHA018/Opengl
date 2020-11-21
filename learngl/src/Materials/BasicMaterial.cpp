#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(unsigned int diffuse, unsigned int specular, float specular_power)
{
	this->x_diffuse_tex = diffuse;
	this->x_specular_tex = specular;
	this->x_specular_power = specular_power;
	this->Materialtype = 1;
}

void BasicMaterial::AssignMaterial(SJ_engine::SJ_shader::shader* obj)
{
	obj->SetUniform1i("type", Materialtype);
	obj->SetUniform1i("u_material.base.diffuse", x_diffuse_tex);
	obj->SetUniform1i("u_material.base.specular", x_specular_tex);
	obj->SetUniform1f("u_material.base.specular_strength", x_specular_power);
}


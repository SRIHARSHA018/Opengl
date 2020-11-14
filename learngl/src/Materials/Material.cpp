#include "Material.h"

Material::Material(unsigned int diffuse, float specular_power, unsigned int specular)
{
	x_diffuse_tex = diffuse;
	x_specular_power = specular_power;
	x_specular_tex = specular;
}

void Material::AssignMaterial(SJ_engine::SJ_shader::shader* obj)
{
	obj->SetUniform1i("u_material.diffuse", x_diffuse_tex);
	obj->SetUniform1i("u_material.specular", x_specular_tex);
	obj->SetUniform1f("u_material.specular_strength", 256.f);
}




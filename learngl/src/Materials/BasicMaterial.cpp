#include "BasicMaterial.h"

BasicMaterial::BasicMaterial()
{
	this->Materialtype = 1;
}

BasicMaterial::BasicMaterial(unsigned int diffuse, unsigned int specular, float specular_power)
{
	this->x_diffuse_tex = diffuse;
	this->x_specular_tex = specular;
	this->x_specular_power = specular_power;
	this->Materialtype = 1;
}





#include"StandardMaterial.h"


StandardMaterial::StandardMaterial(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, float shininess)
{
	this->x_ambient = ambient;
	this->x_diffuse = diffuse;
	this->x_specular = specular;
	this->x_shininess = shininess;
	this->Materialtype = 0;
}

void StandardMaterial::AssignMaterial(SJ_engine::SJ_shader::shader* obj)
{
	obj->SetUniform3fv("u_material.standard.ambient", x_ambient);
	obj->SetUniform3fv("u_material.standard.diffuse", x_diffuse);
	obj->SetUniform3fv("u_material.standard.specular", x_specular);
	obj->SetUniform1f("u_material.standard.shininess", x_shininess*128.f);
	obj->SetUniform1i("type", Materialtype);
}

StandardMaterial::StandardMaterial(Materials name)
{
	this->Materialtype = 0;
	SetMaterialName(name);
	switch (x_name)
	{
	case emerald:
		this->x_ambient = glm::vec3(0.0215, 0.1745, 0.0215);
		this->x_diffuse = glm::vec3(0.07568, 0.61424, 0.07568);
		this->x_specular = glm::vec3(0.633, 0.727811, 0.633);
		this->x_shininess = 0.6f;
		break;
	case jade:
		this->x_ambient = glm::vec3(0.135, 0.2225, 0.1575);
		this->x_diffuse = glm::vec3(0.54, 0.89, 0.63);
		this->x_specular = glm::vec3(0.316228, 0.316228, 0.316228);
		this->x_shininess = 0.1f;
		break;
	case obsidian:
		this->x_ambient = glm::vec3(0.05375,0.05,0.06625);
		this->x_diffuse = glm::vec3(0.18275,0.17,0.22525);
		this->x_specular = glm::vec3(0.332741,0.328634,0.346435);
		this->x_shininess = 0.3f;
		break;
	case pearl:
		this->x_ambient = glm::vec3(0.25,0.20725,0.20725);
		this->x_diffuse = glm::vec3(1,0.829,0.829);
		this->x_specular = glm::vec3(0.296648,0.296648,0.296648);
		this->x_shininess = 0.088f;
		break;
	case gold:
		this->x_ambient = glm::vec3(0.24725, 0.1995, 0.0745);
		this->x_diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
		this->x_specular = glm::vec3(0.628281, 0.555802, 0.366065);
		this->x_shininess = 0.4f;
		break;
	case ruby:
		this->x_ambient = glm::vec3(0.1745,0.01175,0.01175);
		this->x_diffuse = glm::vec3(0.61424,0.04136	,0.04136);
		this->x_specular = glm::vec3(0.727811,0.626959,0.626959);
		this->x_shininess = 0.6f;
		break;
	case turquoise:
		this->x_ambient = glm::vec3(0.1,0.18725	,0.1745);
		this->x_diffuse = glm::vec3(0.396,0.74151,0.69102);
		this->x_specular = glm::vec3(0.297254,0.30829,0.306678);
		this->x_shininess = 0.1f;
		break;
	case brass:
		this->x_ambient = glm::vec3(0.329412,0.223529,0.027451);
		this->x_diffuse = glm::vec3(0.780392,0.568627,0.113725);
		this->x_specular = glm::vec3(0.992157,0.941176,0.807843);
		this->x_shininess = 0.21794872f;
		break;
	case bronze:
		this->x_ambient = glm::vec3(0.2125,0.1275,0.054);
		this->x_diffuse = glm::vec3(0.714,0.4284,0.18144);
		this->x_specular = glm::vec3(0.393548,0.271906,0.166721);
		this->x_shininess = 0.2f;
		break;
	case chrome:
		this->x_ambient = glm::vec3(0.25f);
		this->x_diffuse = glm::vec3(0.4f);
		this->x_specular = glm::vec3(0.774597,0.774597,0.774597);
		this->x_shininess = 0.6f;
		break;
	case copper:
		this->x_ambient = glm::vec3(0.19125,0.0735,0.0225);
		this->x_diffuse = glm::vec3(0.7038,0.27048,0.0828);
		this->x_specular = glm::vec3(0.256777,0.137622,0.086014);
		this->x_shininess = 0.1f;
		break;
	case silver:
		this->x_ambient = glm::vec3(0.19225,0.19225,0.19225);
		this->x_diffuse = glm::vec3(0.50754,0.50754,0.50754);
		this->x_specular = glm::vec3(0.508273,0.508273,0.508273);
		this->x_shininess = 0.4f;
		break;
	case plastic:
		this->x_ambient = glm::vec3(0.0f);
		this->x_diffuse = glm::vec3(0.55f);
		this->x_specular = glm::vec3(0.70f);
		this->x_shininess = 0.25f;
		break;	
	case rubber:
		this->x_ambient = glm::vec3(0.05f);
		this->x_diffuse = glm::vec3(0.5f);
		this->x_specular = glm::vec3(0.70f);
		this->x_shininess = 0.78125;
		break;
	default: std::cout << "Select any material" << std::endl;
	}
}
void StandardMaterial::SetMaterialName(Materials name)
{
	x_name = name;
}
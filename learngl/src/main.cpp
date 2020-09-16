//includes
#include"dependencies.h"
#include"resources/Camera/Camera.h"
//Main function
int main()
{
	SJ_engine::Cl_window Cl_window(1270,720,"SJ_engine");
	std::cout << glGetString(GL_VERSION) << std:: endl;
	//buffer gen and binding
	SJ_engine::SJ_shader::shader shade(&Cl_window);
	shade.GenBindData();
	SJ_engine::SJ_camera::Camera Camera(glm::vec3(0.f,0.f,0.f),2.f,0.2f,0.f,0.f);
	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.clear();
		shade.Color_RotateIt(&Cl_window);
		//navigation and control
		Camera.keycontrol(&Cl_window, &shade);
		glDrawElements(GL_TRIANGLES,6*12,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shade.shaderdestroy();
	//exits application
	return 0;

}


//includes
#include"Camera/Camera.h"
#include"Shaders/shader.h"
#include"textures/texture.h"
//Main function
int main()
{
	SJ_engine::Cl_window Cl_window(1270,720,"SJ_engine");
	//opengl info
	std::cout << glGetString(GL_VERSION) << "\n";
	//buffer gen and binding
	SJ_engine::SJ_shader::shader shader;
	Texture texture("src/textures/checkerboard.jpg");
	texture.Bind();	
	//Texture texture2("resources/textures/me.jpeg");
	//texture2.Bind(1);
	shader.GenBindData();	
	//perspective camera
	SJ_engine::SJ_camera::Camera Camera(glm::vec3(0.f,0.f,0.f),2.f,0.2f,0.f,0.f);
	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.clear();
		Camera.keycontrol(&Cl_window, &shader);
		texture.Bind();
		//navigation and control
		glDrawElements(GL_TRIANGLES,6*12,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shader.shaderdestroy();
	//exits application
	return 0;
}


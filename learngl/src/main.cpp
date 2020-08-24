#include"dependencies.h"
#include"src/graphics/Cl_window.h"
#include"resources/Shaders/shader.h"
//Main function
int main()
{
	using namespace SJ_engine;
	using namespace SJ_shader;
	Cl_window Cl_window(960,640,"SJ_engine");
	std::cout << glGetString(GL_VERSION) << std:: endl;
	//buffer gen and binding
	shader shade;
	shade.GenBindData();
	shade.get_Program_Shader();
	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.InputKeys();
		Cl_window.clear();
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shade.shaderdestroy();
	return 0;

}


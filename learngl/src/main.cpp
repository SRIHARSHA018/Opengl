//includes
#include"dependencies.h"
#include"resources/Shaders/shader.h"
//Main function
int main()
{
	using namespace SJ_engine;
	using namespace SJ_shader;
	Cl_window Cl_window(1270,720,"SJ_engine");
	std::cout << glGetString(GL_VERSION) << std:: endl;
	//buffer gen and binding
	shader shade;
	shade.GenBindData();
	//program intiating
	shade.UseShaderProgram(&Cl_window);
	//loop to progress

	while (!Cl_window.closed())
	{
		Cl_window.clear();
		shade.Color_RotateIt(&Cl_window);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shade.shaderdestroy();
	//exits application
	return 0;

}


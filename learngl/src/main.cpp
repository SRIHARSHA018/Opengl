//includes
#include"dependencies.h"
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
	//program intiating
	shade.UseShaderProgram();
	//loop to progress
	while (!Cl_window.closed())
	{
		
		Cl_window.clear();
		shade.ColorIt(&Cl_window);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shade.shaderdestroy();
	//exits application
	return 0;

}


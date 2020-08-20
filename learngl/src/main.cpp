#include"dependencies.h"
#include"src/graphics/Cl_window.h"
#include"resources/Shaders/shader.h"

int main()
{
	using namespace SJ_engine;
	using namespace SJ_shader;
	Cl_window Cl_window(720, 1270, "SJ_engine");
	std::cout << glGetString(GL_VERSION) << std:: endl;
	unsigned int buffers;
	float positions[6] =
	{
		-0.2,0,
		 0,0.2,
		 0.2,0,
	};
	glGenBuffers(1, &buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	shader shade;
	shade.get_Program_Shader();
	while (!Cl_window.closed())
	{

		Cl_window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Cl_window.Update();

	}
	shade.shaderdestroy();
	return 0;

}


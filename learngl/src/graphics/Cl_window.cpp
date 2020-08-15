#include "Cl_window.h"
namespace SJ_engine {
	void ResizeWindow(GLFWwindow * window,int Width,int Height)
	{
		glViewport(0, 0, Width, Height);
	}
	Cl_window::Cl_window(int Width, int Height, const char* Title)
	{
		x_Win_Width = Width;
		x_Win_Height = Height;
		x_Name = Title;
		if (!Init())
		{
			glfwTerminate();
		}
	}
	Cl_window::~Cl_window()
	{
		glfwTerminate();
	}
	bool SJ_engine::Cl_window::Init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to load Glfw Window" << std::endl;
			return false;
		}
		std::cout << "hello" << std::endl;
		x_window = glfwCreateWindow(x_Win_Width, x_Win_Height, x_Name, NULL, NULL);
		if(!x_window)
		{
			std::cout << "failed to create  a window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(x_window);
		glfwSetWindowSizeCallback(x_window, ResizeWindow);
		return true;

	}
	const bool Cl_window::closed()
	{
		return glfwWindowShouldClose(x_window)==1;
	}
	void Cl_window::Update()
	{
		glfwSwapBuffers(x_window);
		glfwPollEvents();
	}
	void Cl_window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
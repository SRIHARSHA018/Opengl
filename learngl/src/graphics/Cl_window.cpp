#include"Cl_window.h"
namespace SJ_engine {
	//prototype for window resize when callback
	void ResizeWindow(GLFWwindow * window,int Width,int Height)
	{
		glViewport(0, 0, Width, Height);
	}
	//constrctor to intialize the window creation
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
	//destructor to kill the window
	Cl_window::~Cl_window()
	{
		glfwTerminate();
	}
	bool SJ_engine::Cl_window::Init()
	{
		//GLFW intialization and Window Creation
		if (!glfwInit())
		{
			std::cout << "Failed to load Glfw Window" << std::endl;
			return false;
		}
		std::cout << "SJ_engine" << std::endl;
		x_window = glfwCreateWindow(x_Win_Width, x_Win_Height, x_Name, NULL, NULL);
		if(!x_window)
		{
			std::cout << "failed to create  a window" << std::endl;
			return false;
		}
		//OpenGL version setup and GLEW initialization
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 6);
		glfwMakeContextCurrent(x_window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to intialize Glew" << std::endl;
		}
		//Render settings for openGL 4.6
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_FACE, GL_LINE);
		//Resize callback
		glfwSetWindowSizeCallback(x_window, ResizeWindow);
		return true;

	}
	//closing event
	const bool Cl_window::closed()
	{
		return glfwWindowShouldClose(x_window)==1;
	}
	//window poll events
	void Cl_window::Update()
	{
		glfwSwapBuffers(x_window);
		glfwPollEvents();
	}
	//window clear events
	void Cl_window::clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	//Esc key closes window
	void Cl_window::InputKeys()
	{
		if (glfwGetKey(x_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			std::cout << "User pressed exit" << std::endl;
			//setting up window to close
			glfwSetWindowShouldClose(x_window, true);
			
		}
	}

}
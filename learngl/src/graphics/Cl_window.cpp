#include"Cl_window.h"

namespace SJ_engine {
	//input keys processing
	void Cl_window::InputKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Cl_window* win = static_cast<Cl_window*>(glfwGetWindowUserPointer(window));
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			std::cout << "ESC::window closed by user" << std::endl;
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			std::cout << "1::intializing vertex interpolation" << std::endl;
			win->ColorShift = false;
		}
		if (key > 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				win->keys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				win->keys[key] = false;
			}
		}
	}
	void Cl_window::Mouse_button_fun(GLFWwindow* window, int button, int action, int mods)
	{
		Cl_window* win = static_cast<Cl_window*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
			{
				win->mousebuttons[button] = true;				
			}
			else if (action == GLFW_RELEASE)
			{
				win->mousebuttons[button] = false;
			}
	}
	
	//cursor position processing
	void Cl_window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Cl_window* win = static_cast<Cl_window*>(glfwGetWindowUserPointer(window));
		if (win->MouseFirstMoved)
		{
			win->xcursorLast = xpos;
			win->ycursorLast = ypos;
			win->MouseFirstMoved = false;
		}
		win->xChange = xpos - win->xcursorLast;
		win->yChange = win->ycursorLast - ypos;

		win->xcursorLast = xpos;
		win->ycursorLast = ypos;
	}
	//prototype for window resize when callback
	void ResizeWindow(GLFWwindow * window,int Width,int Height)
	{
		glViewport(0, 0,Width,Height);
	}
	//constrctor to intialize the window creation
	Cl_window::Cl_window(int Width, int Height, const char* Title)
	{
		x_Win_Width = Width;
		x_Win_Height = Height;
		x_Name = Title;
		AspectRatio = (float)x_Win_Width / (float)x_Win_Height;
		for(int i=0;i<1024;i++)
		{
			keys[i] = false;
		}
		for(int i=0;i<3;i++)
		{
			mousebuttons[i] = false;
		}
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
		glfwSetWindowUserPointer(x_window, this);
		glfwGetFramebufferSize(x_window, &ScreenWidth, &ScreenHeight);
		AspectRatio = (float)ScreenWidth / (float)ScreenHeight;
		//swap interval for swap buffers period in order to vsync 
		glfwSwapInterval(1);
		//GLEW intialization
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to intialize Glew" << std::endl;
		}
		//Render settings for openGL 4.6 Culling and blend func
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_FACE, GL_LINE);
		//Resize callback
		glfwSetWindowSizeCallback(x_window, ResizeWindow);
		//callback for input keys
		glfwSetKeyCallback(x_window, InputKeys);
		glfwSetMouseButtonCallback(x_window, Mouse_button_fun);
		glfwSetCursorPosCallback(x_window, cursor_position_callback);
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


}
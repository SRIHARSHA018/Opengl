#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GLM/glm.hpp>
#include<iostream>

//global variables
//CLASS for a Window

namespace SJ_engine {
	
	class Cl_window 
	{
	public:
		Cl_window(int Windth, int Height, const char* Title);
		~Cl_window();
		bool Init();
		const bool closed();
		GLFWwindow* Get_Window()const { return x_window; }
		void Update();
		void clear(const glm::vec3 &bg_color);
		bool ColorShift = true;
		float AspectRatio;
		int ScreenWidth, ScreenHeight;
		bool keys[1024];
		bool mousebuttons[3];
		double xChange;
		double yChange;
		double xcursorLast = 0;
		bool MouseFirstMoved = true;
		double ycursorLast = 0;
		float GetAspectRatio();
	private:
		static void InputKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void Mouse_button_fun(GLFWwindow* window, int button, int action, int mods);
		int x_Win_Height, x_Win_Width;
		const char* x_Name;
		GLFWwindow* x_window;
	};
	
}

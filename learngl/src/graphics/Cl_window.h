#pragma once
#include"src/dependencies.h"
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
		void Update();
		void clear();
		bool ColorShift = true;
		float AspectRatio;
		int ScreenWidth, ScreenHeight;
	private:
		static void InputKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
		int x_Win_Height, x_Win_Width;
		const char* x_Name;
		GLFWwindow* x_window;
	};
}

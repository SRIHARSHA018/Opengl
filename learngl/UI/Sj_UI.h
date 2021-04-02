#pragma once
#include"resources/vendor/ImGui/imgui_impl_glfw.h"
#include"resources/vendor/ImGui/imgui_impl_opengl3.h"
#include"src/graphics/Cl_window.h"

class Sj_UI
{
private:
	void x_INIT_UI();
	SJ_engine::Cl_window* x_window;
	std::string x_OpenglVersion;

public:
	Sj_UI(SJ_engine::Cl_window* obj, const std::string& version);
	void SwapFrames();
	
};
#include"Sj_UI.h"

void Sj_UI::x_INIT_UI()
{

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(x_window->Get_Window(), true);
	ImGui_ImplOpenGL3_Init(x_OpenglVersion.c_str());
	ImGui::StyleColorsDark();

}

Sj_UI::Sj_UI(SJ_engine::Cl_window* obj, const std::string& version)
{

	this->x_window = obj;
	std::string Version = "#version " + version;
	this->x_OpenglVersion = Version;
	x_INIT_UI();

}

void Sj_UI::SwapFrames()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}

#include"dependencies.h"

int main()
{
	using namespace SJ_engine;
	Cl_window Cl_window(500, 600, "SJ_engine");
	while(!Cl_window.closed())
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		Cl_window.clear();
		glColor3f(0.f, 1.f, 0.f);
		glBegin(GL_POLYGON);
		glVertex2f(-0.2f,0);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0, 0.2f);
		glVertex2f(0.5f,0.5f);
		glVertex2f(0.2f, 0);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0, -0.2f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
		Cl_window.Update();

	}
	return 0;

}


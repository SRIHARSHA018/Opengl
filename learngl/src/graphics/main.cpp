#include"dependencies.h"
#define GL_PI 3.1415f

void Renderscene(void)
{
	static GLfloat fElect1 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.1f, 1.0f,1.f);
	glBegin(GL_POLYGON);
	glVertex2f(0.f, 20.f);
	glVertex2f(25.f, 25.f);
	glVertex2f(20.f, 0.f);
	glVertex2f(25.f, -25.f);
	glVertex2f(0.f, -20.f);
	glVertex2f(-25.f, -25.f);
	glVertex2f(-20.f, 0.f);
	glVertex2f(-25.f, 25.f);
	glEnd();

	glutSwapBuffers();

}



void SetupRC(void)
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glColor3f(0.f, 1.0f, 0.0f);
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
	{
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w /(GLfloat) h;
	if (w <= h)
	{
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100 / aspectRatio, 1.0, -1.0);

	}
	else
		glOrtho(-100.0*aspectRatio,100.0*aspectRatio,-100.0,100.0,1.0,-1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("S_engine");
	glutDisplayFunc(Renderscene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
	
	return 0;

}
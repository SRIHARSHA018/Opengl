//includes

#include"graphics/Cl_window.h"
#include"src/textures/texture.h"
#include"Lights/Light.h"
#include"Camera/Camera.h"

//Main function
int main()
{

	SJ_engine::Cl_window Cl_window(1080,1080,"SJ_engine");
	SJ_engine::SJ_camera::Camera camera(glm::vec3(0.f, 0.f, 5.f), 2.f, 0.2f, -90.f, 0.f);
	SJ_engine::SJ_shader::shader shader;
	Light light(0.2f, 1.f, 1.f, 1.0f);
	Texture texture("src/textures/checkerboard.jpg");
	//opengl info
	std::cout << glGetString(GL_VERSION) << "\n";
	//buffer gen and binding
	shader.GenBindData();
	texture.Bind();
	//perspective
	glm::mat4 proj = glm::perspective(glm::radians(45.f),Cl_window.GetAspectRatio(), 0.1f, 100.f);
	//shader uniform binds
	shader.SetUniform1f("u_Texture", 0);
	shader.SetUniformMatrix4f("u_Projection", 1, proj);
	shader.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
	shader.SetUniformMatrix4f("u_model", 1,camera.getModelMatrix());
	shader.SetUniform3fv("u_cameraPos", camera.getcamPos());
	shader.SetUniform3fv("u_directional_light.Lightcolor", light.GetLightColor());
	shader.SetUniform1f("u_directional_light.a_intensity", light.GetAmbientIntensity());
	
	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.clear();
		shader.UseShaderProgram();
		camera.update();
		camera.keycontrol(&Cl_window, &shader);
		texture.Bind();

		glm::mat4 proj = glm::perspective(glm::radians(45.f),Cl_window.GetAspectRatio(), 0.1f, 100.f);

		shader.SetUniform1f("u_Texture", 0);
		shader.SetUniformMatrix4f("u_Projection", 1, proj);
		shader.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		shader.SetUniformMatrix4f("u_model", 1,camera.getModelMatrix());		
		shader.SetUniform3fv("u_cameraPos", camera.getcamPos());
		shader.SetUniform3fv("u_directional_light.Lightcolor", light.GetLightColor());
		shader.SetUniform1f("u_directional_light.a_intensity", light.GetAmbientIntensity());

		//coordinate lines
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 10.f);
		glEnd();

		//navigation and control
		glDrawElements(GL_TRIANGLES,6*12,GL_UNSIGNED_INT,nullptr);
		Cl_window.Update();
	}
	//destroy the shader program
	shader.shaderdestroy();
	//exits application
	return 0;
}


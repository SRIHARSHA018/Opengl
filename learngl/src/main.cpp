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
	SJ_engine::SJ_shader::shader cube("resources/basic_shaders/core_vs.shader", "resources/basic_shaders/core_fs.shader");
	Light light(0.1f, 1.f, 1.f, 1.0f,
		1.f,glm::vec3(1.f,1.f,1.f),1.0f,250.f);
	Texture texture("src/textures/checkerboard.jpg");
	//opengl info
	std::cout << glGetString(GL_VERSION) << "\n";
	//buffer gen and binding
	cube.GenBindData();
	texture.Bind();
	//perspective
	glm::mat4 proj = glm::perspective(glm::radians(45.f),Cl_window.GetAspectRatio(), 0.1f, 100.f);
	//shader uniform binds
	cube.SetUniform1f("u_Texture", 0);
	cube.SetUniformMatrix4f("u_Projection", 1, proj);
	cube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
	cube.SetUniformMatrix4f("u_model", 1,camera.getModelMatrix());
	cube.SetUniform3fv("u_cameraPos", camera.getcamPos());
	cube.SetUniform3fv("u_directional_light.LightColor", light.GetLightColor());
	cube.SetUniform1f("u_directional_light.a_intensity", light.GetAmbientIntensity());
	cube.SetUniform3fv("u_directional_light.DiffuseDirection", light.GetDiffuseDirection());
	cube.SetUniform1f("u_directional_light.DiffuseIntensity", light.GetDiffuseIntensity());
	cube.SetUniform1f("u_directional_light.SpecularIntensity", light.GetSpecularIntensity());
	cube.SetUniform1f("u_directional_light.SpecularIntensity", light.GetSpecularIntensity());

	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.clear();
		cube.UseShaderProgram();
		camera.update();
		camera.keycontrol(&Cl_window, &cube);
		texture.Bind();

		glm::mat4 proj = glm::perspective(glm::radians(45.f),Cl_window.GetAspectRatio(), 0.1f, 100.f);

		cube.SetUniform1f("u_Texture", 0);
		cube.SetUniformMatrix4f("u_Projection", 1, proj);
		cube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		cube.SetUniformMatrix4f("u_model", 1,camera.getModelMatrix());		
		cube.SetUniform3fv("u_cameraPos", camera.getcamPos());
		cube.SetUniform3fv("u_directional_light.LightColor", light.GetLightColor());
		cube.SetUniform1f("u_directional_light.a_intensity", light.GetAmbientIntensity());
		cube.SetUniform3fv("u_directional_light.DiffuseDirection", light.GetDiffuseDirection());
		cube.SetUniform1f("u_directional_light.DiffuseIntensity", light.GetDiffuseIntensity());
		cube.SetUniform1f("u_directional_light.SpecularPower", light.GetSpecularPower());
		cube.SetUniform1f("u_directional_light.SpecularPower", light.GetSpecularPower());

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
		glDrawArrays(GL_TRIANGLES, 0, 36);
		Cl_window.Update();
	}
	//destroy the shader program
	cube.shaderdestroy();
	//exits application
	return 0;
}


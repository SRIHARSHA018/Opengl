//includes
#include"graphics/Cl_window.h"
#include"src/textures/texture.h"
#include"Camera/Camera.h"
#include"resources/vendor/ImGui/imgui_impl_glfw.h"
#include "resources/vendor/ImGui/imgui_impl_opengl3.h"

//Main function
int main()
{
	SJ_engine::Cl_window Cl_window(1080, 1080, "SJ_engine");

	//opengl info
	std::cout << glGetString(GL_VERSION) << "\n";

	//imGui
	// Setup Platform/Renderer bindings
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Cl_window.Get_Window(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();

	//imgui contents
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glm::vec3 LightDirection(1.0f, 0.f, 0.f);
	glm::vec3 PointLightColor(1.f, 1.f, 1.f);
	glm::vec3 bgColor(0.2f, 0.3f, 0.3f);
	glm::vec3 pointLightPosition(0.f, 0.f, 0.f);

	//camera
	SJ_engine::SJ_camera::Camera camera(glm::vec3(0.f, 0.f, 5.f), 2.f, 0.2f, -90.f, 0.f);

	//meshes
	SJ_engine::SJ_shader::shader cube("resources/basic_shaders/core_vs.shader", "resources/basic_shaders/core_fs.shader");

	SJ_engine::SJ_shader::shader lightcube("resources/basic_shaders/lightsources/v_sourceObject.shader",
		"resources/basic_shaders/lightsources/f_sourceObject.shader");
	SJ_engine::SJ_shader::shader PointLightCube("resources/basic_shaders/lightsources/v_sourceObject.shader",
	 	"resources/basic_shaders/lightsources/f_sourceObject.shader");
	
	//lights
	DirectionalLight light(0.05f, 1.f, 1.f, 1.f,
		3.f, glm::vec3(1.f, 1.f, 1.f));

	PointLight pointLight(0.05f,PointLightColor.x,PointLightColor.y,PointLightColor.z, 1.f);
	pointLight.SetAttenuationParameters(0.032f, 0.09f, 1.0f);

	//Textures
	Texture diffuse("src/textures/checkerboard.jpg");
	diffuse.Bind();

	
	//buffer gen and binding
	cube.GenBindData();

	//perspective
	glm::mat4 proj = glm::perspective(glm::radians(45.f), Cl_window.GetAspectRatio(), 0.1f, 100.f);

	//loop to progress
	while (!Cl_window.closed())
	{
		Cl_window.clear(bgColor);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		camera.update();
		camera.keycontrol(&Cl_window, &cube);
		glm::mat4 proj = glm::perspective(glm::radians(45.f), Cl_window.GetAspectRatio(), 0.1f, 100.f);
		
		//CubeMesh
		cube.UseShaderProgram();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		cube.SetUniform3fv("u_cameraPos", camera.getcamPos());
		cube.SetUniform1f("u_material.Diffuse", 0);
		cube.SetUniform1f("u_material.specular_intensity", 1.f);
		cube.SetUniform1f("u_material.specular_strength", 32.f);
		cube.SetUniformMatrix4f("u_Projection", 1, proj);
		cube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		cube.SetUniformMatrix4f("u_model", 1, camera.getModelMatrix());
		cube.SetDirectionalLightUniforms(&light);
		cube.SetPointLightUniforms(&pointLight);

		//coordinate lines
		glBegin(GL_LINES);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 10.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 10.f);
		glEnd();


		//DirectionalLight object
		lightcube.UseShaderProgram();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightcube.SetUniformMatrix4f("u_Projection", 1, proj);
		lightcube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(LightDirection);
		model = glm::scale(model, glm::vec3(0.2f));
		lightcube.SetUniformMatrix4f("u_model", 1, model);
		lightcube.SetUniform3fv("u_lightColor", light.GetLightColor());
		lightcube.SetUniform1f("u_intensity", light.GetDiffuseIntensity());
		light.SetLightDirection(LightDirection.x, LightDirection.y, LightDirection.z);

		//PointLightCube
		PointLightCube.UseShaderProgram();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		PointLightCube.SetUniformMatrix4f("u_Projection", 1, proj);
		PointLightCube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		glm::mat4 pointLightmodel = glm::mat4(1.0f);
		pointLightmodel = glm::translate(pointLightPosition);
		pointLightmodel = glm::scale(pointLightmodel, glm::vec3(0.2f));
		PointLightCube.SetUniformMatrix4f("u_model", 1, pointLightmodel);
		PointLightCube.SetUniform3fv("u_lightColor", pointLight.GetLightColor());
		PointLightCube.SetUniform1f("u_intensity", pointLight.GetDiffuseIntensity());
		pointLight.SetPointLightPos(pointLightPosition);
		pointLight.SetLightColor(PointLightColor);
		//imgui window contents
		{

			ImGui::Begin("Background");                          // Create a window called "Hello, world!" and append into it.
			ImGui::ColorEdit3("backgroundColor", &bgColor.x);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Begin("Light");
			ImGui::SliderFloat3("Directional Light", &LightDirection.x, -2.f, 2.f, "%.3f");          // Edit 1 float using a slide from 0.0f to 1.0f
			ImGui::SliderFloat3("Point Light Position", &pointLightPosition.x, -20.f, 20.f, "%.3f");
			ImGui::ColorEdit3("Point Light Color", &PointLightColor.x);
			ImGui::End();
		}
		//navigation and control
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		Cl_window.Update();

	}

	//destroy the shader program
	diffuse.UnBind();
	cube.shaderdestroy();

	//exits application
	return 0;
}
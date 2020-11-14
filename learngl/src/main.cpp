//includes
#include"graphics/Cl_window.h"
#include"src/textures/texture.h"
#include"Camera/Camera.h"
#include"src/Materials/Material.h"
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
	float directionalLightIntensity = 1.f;
	glm::vec3 LightDirection(1.0f, 0.f, 0.f);
	glm::vec3 bgColor(0.f, 0.f, 0.f);
	int PointLightCount =1;
	std::vector<glm::vec3> PointLightColor(PointLightCount, { 1.f,1.f,1.f });
	std::vector<glm::vec3> PointLightPosition(PointLightCount, { 0.f,0.f,0.f });
	    //spotlights imgui
	int SpotLightCount = 1;
	std::vector<glm::vec3> SpotLightColor(SpotLightCount, { 1.f,1.f,1.f });
	std::vector<glm::vec3> SpotLightPosition(SpotLightCount, { 0.f,0.f,0.f });
	std::vector<glm::vec3> SpotLightDirection(SpotLightCount, { 0.f,0.f,-1.f });
	std::vector<float> SpotLightCutOff(SpotLightCount, glm::cos(glm::radians(12.5f)));
	std::vector<float> SpotLightOuterCutOff(SpotLightCount, glm::cos(glm::radians(17.5f)));


	//camera
	SJ_engine::SJ_camera::Camera camera(glm::vec3(0.f, 0.f, 5.f), 2.f, 0.2f, -90.f, 0.f);

	//meshes
	SJ_engine::SJ_shader::shader cube("resources/basic_shaders/core_vs.glsl", "resources/basic_shaders/core_fs.glsl");

	SJ_engine::SJ_shader::shader lightcube("resources/basic_shaders/lightsources/v_sourceObject.glsl",
		"resources/basic_shaders/lightsources/f_sourceObject.glsl");

	//shading positions and indices
	float vertexattribs[] =
	{

		//cube2
		 //back face
		 -0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,0.f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,1.0f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,1.0f,	 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.f,1.0f,    0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f,  0.0f, -1.0f,
		//front face
		-0.5f, -0.5f, 0.5f,		0.f,0.f,	 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f,0.f,	 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		1.f,1.f,	 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		1.f,1.f,	 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		0.f,1.f,	 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.f,0.f,	 0.0f,  0.0f, 1.0f,
	   //left face									 
		  -0.5f,  0.5f,  0.5f,	0.f,0.f,	 -1.0f,  0.0f,  0.0f,
		  -0.5f,  0.5f, -0.5f,	1.0f,0.f,	 -1.0f,  0.0f,  0.0f,
		  -0.5f, -0.5f, -0.5f,	1.f,1.f,	 -1.0f,  0.0f,  0.0f,
		  -0.5f, -0.5f, -0.5f,	1.f,1.f,	 -1.0f,  0.0f,  0.0f,
		  -0.5f, -0.5f,  0.5f,	0.f,1.f,	 -1.0f,  0.0f,  0.0f,
		  -0.5f,  0.5f,  0.5f,	0.f,0.f,	 -1.0f,  0.0f,  0.0f,
	  //RIGHT FACE									 
		  0.5f,  0.5f,  0.5f,	0.f,0.f,     1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,	1.0f,0.f,    1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,	1.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,	1.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,	0.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,	0.f,0.f,     1.0f,  0.0f,  0.0f,
	  //bottom face								 
		 -0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,	1.0f,0.f,	 0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,	1.f,1.f,	 0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,	1.f,1.f,	 0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,	0.f,1.f,	 0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f, -1.0f,  0.0f,
	 //top face
		-0.5f,  0.5f, -0.5f,	0.f,0.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,0.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.f,1.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.f,1.f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.f,1.f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.f,0.f,	 0.0f,  1.0f,  0.0f
	};
	
	//buffers for positions
	VertexBuffer vbo(vertexattribs, sizeof(vertexattribs));

	//VERTEX ATTRIBUTE POSITIONS
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	//VERTEX ATTRIBUTE TEXTURE COORDINATES
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	//VERTEX ATTRIBUTE NORMALS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	//lights
	DirectionalLight light(0.05f, 1.f, 1.f, 1.f,
		3.f, glm::vec3(1.f, 1.f, 1.f));

	PointLight pointlight;
	pointlight.CreatePointLights(PointLightCount);

	SpotLight spotlight;
	spotlight.CreateSpotLights(SpotLightCount);

	//Textures
	Texture diffuse("src/textures/container2.png", 0);
	Texture specular("src/textures/container2_specular.png", 1);
	diffuse.Bind();
	specular.Bind();
	//material
	Material material0(diffuse.GetTextureSlot(), 256.f, specular.GetTextureSlot());

	//loop to progress
	while (!Cl_window.closed())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		Cl_window.clear(bgColor);

		camera.update();
		camera.keycontrol(&Cl_window, &cube);
		//perspective
		glm::mat4 proj=glm::perspective(glm::radians(45.f), Cl_window.GetAspectRatio(), 0.1f, 100.f);
		//CubeMesh
		cube.UseShaderProgram();
		material0.AssignMaterial(&cube);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Camera
		cube.SetUniform3fv("u_cameraPos", camera.getcamPos());
		cube.SetUniformMatrix4f("u_Projection", 1, proj);
		cube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		cube.SetUniformMatrix4f("u_model", 1, camera.getModelMatrix());

		//Lights uniforms
		cube.SetDirectionalLightUniforms(&light);
		cube.SetUniform1f("u_Dir_intensity", directionalLightIntensity);
		cube.SetPointLightUniforms(pointlight.pointLights, pointlight.GetLightsCount());
		cube.SetSpotLightUniforms(spotlight.SpotLights, spotlight.GetLightsCount());

		//DirectionalLight object
		lightcube.UseShaderProgram();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightcube.SetUniformMatrix4f("u_Projection", 1, proj);
		lightcube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		SetLightObject(&light, &lightcube,LightDirection);
		
		//directional light ui
		light.SetLightDirection(LightDirection.x, LightDirection.y, LightDirection.z);
		pointlight.SetPointLightUIcontroller(PointLightColor, PointLightPosition,PointLightCount);
		spotlight.SetSpotLightUIcontroller(SpotLightColor, SpotLightPosition, SpotLightDirection,
			SpotLightCutOff,SpotLightOuterCutOff,
			SpotLightCount);

		//imgui window contents
		{

			ImGui::Begin("Background");                          
			ImGui::ColorEdit3("backgroundColor", &bgColor.x);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Begin("Light");
			ImGui::SliderFloat3("Directional Light", &LightDirection.x, -2.f, 2.f, "%.3f");
			ImGui::SliderFloat("Direcional Light Intensity", &directionalLightIntensity, 0.f, 1.f, "%.3f");
			for (int i = 0; i < PointLightCount; i++)
			{
				std::string pos = "Point Light position" + std::to_string(i);
				std::string color = "Point Light color" + std::to_string(i);
				ImGui::SliderFloat3(pos.c_str(), &PointLightPosition[i].x, -20.f, 20.f, "%.3f");
				ImGui::ColorEdit3(color.c_str(), &PointLightColor[i].x);
			}
			for (int i = 0; i < SpotLightCount; i++)
			{
				std::string pos = "Spot Light position" + std::to_string(i);
				std::string dir = "Spot Light direction" + std::to_string(i);
				std::string cutoff = "Spot Light angle" + std::to_string(i);
				std::string OuterCutoff = "Spot Light Outerangle" + std::to_string(i);
				std::string color = "Spot Light color" + std::to_string(i);
				ImGui::SliderFloat3(pos.c_str(), &SpotLightPosition[i].x, -20.f, 20.f, "%.3f");
				ImGui::SliderFloat3(dir.c_str(), &SpotLightDirection[i].x, -1.f, 1.f, "%.3f");
				ImGui::SliderFloat(cutoff.c_str(), &SpotLightCutOff[i], 0.f, 1.f, "%.3f");
				ImGui::SliderFloat(OuterCutoff.c_str(), &SpotLightOuterCutOff[i], 0.f, 1.f, "%.3f");
				ImGui::ColorEdit3(color.c_str(), &SpotLightColor[i].x);
			}
			ImGui::End();
		}
		//navigation and control
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		Cl_window.Update();

	}

	//destroy the shader program
	diffuse.~Texture();
	specular.~Texture();
	cube.shaderdestroy();

	//exits application
	return 0;
}
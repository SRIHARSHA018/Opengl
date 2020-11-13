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
	float directionalLightIntensity = 1.f;
	glm::vec3 LightDirection(1.0f, 0.f, 0.f);
	glm::vec3 bgColor(0.f, 0.f, 0.f);
	int lightCount =3;
	std::vector<glm::vec3> PointLightColor(lightCount, { 1.f,1.f,1.f });
	std::vector<glm::vec3> PointLightPosition(lightCount, { 0.f,0.f,0.f });

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

	//index buffer
	//it can manage buffer data like Duplicate vertices
	//IndexBuffer ibo(indices,36);

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
	pointlight.CreatePointLights(lightCount);
	
	//Textures
	Texture diffuse("src/textures/checkerboard.jpg");
	diffuse.Bind();
	

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
		cube.SetUniform1f("u_Dir_intensity", directionalLightIntensity);
		cube.SetUniform1i("u_no_lights", pointlight.GetLightsCount());
		cube.SetPointLightUniforms(pointlight.pointLights, pointlight.GetLightsCount());


		//DirectionalLight object
		lightcube.UseShaderProgram();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightcube.SetUniformMatrix4f("u_Projection", 1, proj);
		lightcube.SetUniformMatrix4f("u_View", 1, camera.getViewMatrix());
		SetLightObject(&light, &lightcube,LightDirection);
		
		//directional light ui
		light.SetLightDirection(LightDirection.x, LightDirection.y, LightDirection.z);
		
		pointlight.SetPointLightUIcontroller(PointLightColor, PointLightPosition,lightCount);
		//imgui window contents
		{

			ImGui::Begin("Background");                          
			ImGui::ColorEdit3("backgroundColor", &bgColor.x);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Begin("Light");
			ImGui::SliderFloat3("Directional Light", &LightDirection.x, -2.f, 2.f, "%.3f");
			ImGui::SliderFloat("Direcional Light Intensity", &directionalLightIntensity, 0.f, 1.f, "%.3f");
			for (int i = 0; i < lightCount; i++)
			{
				std::string pos = "Point Light position" + std::to_string(i);
				std::string color = "Point Light color" + std::to_string(i);
				ImGui::SliderFloat3(pos.c_str(), &PointLightPosition[i].x, -20.f, 20.f, "%.3f");
				ImGui::ColorEdit3(color.c_str(), &PointLightColor[i].x);
			}
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
#pragma once
#include<unordered_map>
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLM/gtx/transform.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include"src/Lights/DirectionalLight.h"
#include"src/Lights/PointLight.h"
#include"src/Lights/SpotLight.h"
#include"src/VertexArrays_Buffers/VertexBuffer.h"
#include"src/VertexArrays_Buffers/IndexBuffer.h"

//CLASS for shader
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program_ID;
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader) ;

			//cache list of uniforms
			std::unordered_map<std::string, int> uniformlistCache;

		public:

			shader(const char* vertexshader,const char* fragmentshader);
			~shader();
			void shaderdestroy();
			void UseShaderProgram();
			unsigned int Get_shader_program(){	return x_Shader_Program_ID; }

			//uniforms abstract
			unsigned int GetUniformLocation(const std::string &uniformname);
			void SetUniform3fv(const std::string& uniformname, const glm::vec3& vector3);
			void SetUniform1i(const std::string& uniformname, int value);
			void SetUniform1f(const std::string& uniformname, float value);
			void SetUniformMatrix4f(const std::string &uniformname, int size, const glm::mat4 &matrix);
			void SetDirectionalLightUniforms(DirectionalLight* lightObj);
			void SetPointLightUniforms(std::vector<PointLight>& lightObj,int count);
			void SetSpotLightUniforms(std::vector<SpotLight>& lightObj, int count);
		};

		template<typename C>
		void SetLightObject(C* light, SJ_engine::SJ_shader::shader* obj, glm::vec3& position)
		{
			glm::mat4 Lightmodel = glm::mat4(1.0f);
			Lightmodel = glm::translate(position);
			Lightmodel = glm::scale(Lightmodel, glm::vec3(0.2f));
			obj->SetUniformMatrix4f("u_model", 1, Lightmodel);
			obj->SetUniform3fv("u_lightColor", light->GetLightColor());
			obj->SetUniform1f("u_intensity", light->GetDiffuseIntensity());
		}
	}
}


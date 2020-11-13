#include "shader.h"

namespace SJ_engine {
	namespace SJ_shader {
		shader::shader(const char* vertexshader, const char* fragmentshader)
		{
			char InfoLog[1024];
			std::ifstream file;
			std::string temp = "";
			std::string srcstr = "";
			//vertex shader
			file.open(vertexshader);
			if (file.is_open())
			{
				while (std::getline(file, temp))
				{
					srcstr += temp + "\n";
				}
			}
			else
			{
				std::cout << "ERROR::Vertex Shader file is not loaded" << std::endl;
			}
			file.close();
			unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
			const char* vertexstr = srcstr.c_str();
			glShaderSource(VertexShader, 1, &vertexstr, NULL);
			glCompileShader(VertexShader);
			int vcompile;
			glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &vcompile);
			if (!vcompile)
			{
				glGetShaderInfoLog(VertexShader, 1024, NULL, InfoLog);
				std::cout << "ERROR::Vertex shader compilation failed" << std::endl;
				std::cout << InfoLog << "\n";
			}
			//Fragment shader
			temp = "";
			srcstr = "";
			file.open(fragmentshader);
			if (file.is_open())
			{
				while (std::getline(file, temp))
				{
					srcstr += temp + "\n";
				}
			}
			else
			{
				std::cout << "ERROR::Fragment Shader file is not loaded" << std::endl;
			}
			file.close();
			unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			const char* Fragmentstr = srcstr.c_str();
			glShaderSource(FragmentShader, 1, &Fragmentstr, NULL);
			glCompileShader(FragmentShader);
			int fcompile;
			glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &fcompile);
			if (!fcompile)
			{
				glGetShaderInfoLog(FragmentShader, 1024, NULL, InfoLog);
				std::cout << "ERROR::Fragment shader compilation failed" << std::endl;
				std::cout << InfoLog << "\n";

			}
			x_Shader_Program_ID = createprogram(VertexShader, FragmentShader);
			UseShaderProgram();
		}

		shader::~shader()
		{
			glDeleteShader(x_Shader_Program_ID);
		}

		unsigned int shader::createprogram(unsigned int Vshader, unsigned int Fshader)
		{
			//creating a shader program
			int success;
			unsigned int program = glCreateProgram();
			glAttachShader(program, Vshader);
			glAttachShader(program, Fshader);
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				char InfoLog[512];
				glGetProgramInfoLog(program, 512, NULL, InfoLog);
				std::cout << InfoLog << std::endl;
			}
			glValidateProgram(program);
			glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
			if (!success)
			{
				char InfoLog[512];
				glGetProgramInfoLog(program, 512, NULL, InfoLog);
				std::cout << "ERROR in validating" << InfoLog << std::endl;
			}
			return program;

		}
		void shader::UseShaderProgram()
		{
			glUseProgram(x_Shader_Program_ID);
		}

		void shader::shaderdestroy()
		{
			//Deleting shader program
			glDeleteProgram(x_Shader_Program_ID);
		}

		void shader::SetUniformMatrix4f(const std::string &uniformname, int size, const glm::mat4 &matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(uniformname), size, GL_FALSE, glm::value_ptr(matrix));
		}
		void shader::SetUniform1i(const std::string& uniformname, int value)
		{
			glUniform1i(GetUniformLocation(uniformname), value);
		}
		void shader::SetUniform1f(const std::string& uniformname, float value)
		{
			glUniform1f(GetUniformLocation(uniformname), value);
		}
		void shader::SetUniform3fv(const std::string& uniformname, const glm::vec3& vector3)
		{
			glUniform3fv(GetUniformLocation(uniformname),1, glm::value_ptr(vector3));
		}
		unsigned int  shader::GetUniformLocation(const std::string& uniformname)
		{
			if (uniformlistCache.find(uniformname) != uniformlistCache.end())
			{
				return uniformlistCache[uniformname];
			}
			int loc = glGetUniformLocation(x_Shader_Program_ID, uniformname.c_str());
			uniformlistCache[uniformname] = loc;
			return loc;
		}
		void shader::SetDirectionalLightUniforms(DirectionalLight* lightObj)
		{
			this->SetUniform3fv("u_directional_light.LightColor", lightObj->GetLightColor());
			this->SetUniform1f("u_directional_light.ambient_intensity", lightObj->GetAmbientIntensity());
			this->SetUniform3fv("u_directional_light.DiffuseDirection", lightObj->GetLightDirection());
			this->SetUniform1f("u_directional_light.DiffuseIntensity", lightObj->GetDiffuseIntensity());
			
		}

		void shader::SetPointLightUniforms(std::vector<PointLight>& lightObj,int count)
		{
			for (int i = 0; i < count; i++)
			{
				std::string a = std::to_string(i);
				this->SetUniform1f("u_point_light[" + a + "].ambient_intensity",lightObj[i].GetAmbientIntensity() );
				this->SetUniform1f("u_point_light[" + a + "].DiffuseIntensity", lightObj[i].GetDiffuseIntensity());
				this->SetUniform1f("u_point_light[" + a + "].quadratic", lightObj[i].GetAttenuationQuadratic());
				this->SetUniform1f("u_point_light[" + a + "].linearv", lightObj[i].GetAttenuationLinear());
				this->SetUniform1f("u_point_light[" + a + "].constant", lightObj[i].GetAttenuationConstant());
				this->SetUniform3fv("u_point_light[" + a + "].PointLightPosition", lightObj[i].GetPointLightPos());
				this->SetUniform3fv("u_point_light[" + a + "].LightColor", lightObj[i].GetLightColor());
			}

		}

	}
}


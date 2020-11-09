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

		void shader::GenBindData()
		{
			//shading positions and indices
			float positions[] =
			{
				////plane
				////positions       //texture coords    //normals
				//-1.f,-1.f,0.f,     0.f,0.f,           0.f,0.f,-1.f,
				// 1.f,-1.f,0.f,     1.f,0.f,           0.f,0.f,-1.f,
				// 1.f,1.f,0.f,      1.f,1.f,           0.f,0.f,-1.f,
				// -1.f,1.f,0.f,     0.f,1.f,           0.f,0.f,-1.f
				///*cube*/
				//// front        //texture coordinates  //normals
				// 1.0, -1.0,  1.0,   1.f,0.f,           0.f,0.f,1.f,
				// 1.0,  1.0,  1.0,   1.f,1.f,           0.f,0.f,1.f,
				//-1.0,  1.0,  1.0,   0.f,1.f,           0.f,0.f,1.f,
				//-1.0, -1.0,  1.0,   0.f,0.f,           0.f,0.f,1.f,    
				//// top
				//-1.0,  1.0,  1.0,   0.f,0.f,           0.f,1.f,0.f,
				// 1.0,  1.0,  1.0,	1.f,0.f,		   0.f,1.f,0.f,
				// 1.0,  1.0, -1.0,	1.f,1.f,		   0.f,1.f,0.f,
				//-1.0,  1.0, -1.0,	0.f,1.f,		   0.f,1.f,0.f,
				//// back
				// 1.0, -1.0, -1.0,   0.f,0.f,           0.f,0.f,-1.f,
				//-1.0, -1.0, -1.0,	1.f,0.f,		   0.f,0.f,-1.f,
				//-1.0,  1.0, -1.0,	1.f,1.f,		   0.f,0.f,-1.f,
				// 1.0,  1.0, -1.0,	0.f,1.f,		   0.f,0.f,-1.f,
				// // bottom
				// -1.0, -1.0, -1.0,  0.f,0.f,           0.f,-1.f,0.f,
				//  1.0, -1.0, -1.0,	1.f,0.f,		   0.f,-1.f,0.f,
				//  1.0, -1.0,  1.0,	1.f,1.f,		   0.f,-1.f,0.f,
				// -1.0, -1.0,  1.0,	0.f,1.f,		   0.f,-1.f,0.f,
				// // left									   
				// -1.0, -1.0, -1.0,  0.f,0.f,           -1.f,0.f,0.f,
				// -1.0, -1.0,  1.0,	1.f,0.f,		   -1.f,0.f,0.f,
				// -1.0,  1.0,  1.0,	1.f,1.f,		   -1.f,0.f,0.f,
				// -1.0,  1.0, -1.0,	0.f,1.f,		   -1.f,0.f,0.f,
				// // right									   
				//  1.0, -1.0,  1.0,  0.f,0.f,           1.f,0.f,0.f,
				//  1.0, -1.0, -1.0,	1.f,0.f,		   1.f,0.f,0.f,
				//  1.0,  1.0, -1.0,	1.f,1.f,		   1.f,0.f,0.f,
				//  1.0,  1.0,  1.0,	0.f,1.f,		   1.f,0.f,0.f,

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
			unsigned int indices[] =
			{
				////plane
				//0,1,2,
				//0,2,3
				//cube
				// front
				0,  1,  2,
				2,  3,  0,
				// top
				4,  5,  6,
				6,  7,  4,
				// back
				8,  9, 10,
				10, 11,  8,
				// bottom
				12, 13, 14,
				14, 15, 12,
				// left
				16, 17, 18,
				18, 19, 16,
				// right
				20, 21, 22,
				22, 23, 20,
				
			};

			//buffers for positions
			unsigned int buffers;
			glGenBuffers(1, &buffers);
			glBindBuffer(GL_ARRAY_BUFFER, buffers);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			
			//VERTEX ATTRIBUTE POSITIONS
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*) 0);
			
			//index buffer
			//it can manage buffer data like Duplicate vertices 
			/*unsigned int indexbufferobj;
			glGenBuffers(1, &indexbufferobj);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferobj);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

			//VERTEX ATTRIBUTE TEXTURE COORDINATES
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

			//VERTEX ATTRIBUTE NORMALS
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
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
		void shader::SetPointLightUniforms(PointLight* lightObj)
		{
			this->SetUniform3fv("u_point_light.PointLightPosition", lightObj->GetPointLightPos());
			this->SetUniform1f("u_point_light.ambient_intensity", lightObj->GetAmbientIntensity());
			this->SetUniform1f("u_point_light.DiffuseIntensity", lightObj->GetDiffuseIntensity());
			this->SetUniform3fv("u_point_light.LightColor", lightObj->GetLightColor());
			this->SetUniform1f("u_point_light.quadratic", lightObj->GetAttenuationQuadratic());
			this->SetUniform1f("u_point_light.linearv", lightObj->GetAttenuationLinear());
			this->SetUniform1f("u_point_light.constant", lightObj->GetAttenuationConstant());
		}
	}
}


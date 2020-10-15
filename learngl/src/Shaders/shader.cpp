#include "shader.h"

namespace SJ_engine {
	namespace SJ_shader {
		shader::shader()
		{
			char InfoLog[1024];
			std::ifstream file;
			std::string temp = "";
			std::string srcstr = "";
			//vertex shader
			file.open("resources/basic_shaders/core_vs.shader");
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
			file.open("resources/basic_shaders/core_fs.shader");
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
			modelmatrix();
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
				// front            //texture coordinates
				-1.0, -1.0,  1.0,   0.f,0.f,
				 1.0, -1.0,  1.0,   1.f,0.f,
				 1.0,  1.0,  1.0,   1.f,1.f,
				-1.0,  1.0,  1.0,   0.f,1.f,
				// top
				-1.0,  1.0,  1.0,   0.f,0.f,
				 1.0,  1.0,  1.0,	1.f,0.f,
				 1.0,  1.0, -1.0,	1.f,1.f,
				-1.0,  1.0, -1.0,	0.f,1.f,
				// back
				 1.0, -1.0, -1.0,   0.f,0.f,
				-1.0, -1.0, -1.0,	1.f,0.f,
				-1.0,  1.0, -1.0,	1.f,1.f,
				 1.0,  1.0, -1.0,	0.f,1.f,
				 // bottom
				 -1.0, -1.0, -1.0,  0.f,0.f,
				  1.0, -1.0, -1.0,	1.f,0.f,
				  1.0, -1.0,  1.0,	1.f,1.f,
				 -1.0, -1.0,  1.0,	0.f,1.f,
				 // left
				 -1.0, -1.0, -1.0,  0.f,0.f,
				 -1.0, -1.0,  1.0,	1.f,0.f,
				 -1.0,  1.0,  1.0,	1.f,1.f,
				 -1.0,  1.0, -1.0,	0.f,1.f,
				 // right
				  1.0, -1.0,  1.0,  0.f,0.f,
				  1.0, -1.0, -1.0,	1.f,0.f,
				  1.0,  1.0, -1.0,	1.f,1.f,
				  1.0,  1.0,  1.0,	0.f,1.f,

			};
			unsigned int indices[] =
			{
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
			//vertex attributes enble and pointing them
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
			//index buffer
			//it can manage buffer data like Duplicate vertices 
			unsigned int indexbufferobj;
			glGenBuffers(1, &indexbufferobj);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferobj);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			//texturebind
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			SetUniform1i("u_Texture", 0);

		}

		void shader::shaderdestroy()
		{
			//Deleting shader program
			glDeleteProgram(x_Shader_Program_ID);
		}

		void shader::modelmatrix()
		{
			//model matrix
			model = glm::translate(model, glm::vec3(0.f, 0.f, -1.f));
			model = glm::rotate(model, 45.f, glm::vec3(1.f, 0.f, 0.f));
			model = glm::rotate(model, 45.f, glm::vec3(0.f, 1.f, 0.f));
			model = glm::rotate(model, 45.f, glm::vec3(0.f, 0.f, 1.f));
			model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
			SetUniformMatrix4f("u_model", 1, model);
		}

		void shader::SetUniformMatrix4f(const std::string &uniformname, int size, const glm::mat4 &matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(uniformname), size, GL_FALSE, glm::value_ptr(matrix));
		}
		void shader::SetUniform1i(const std::string& uniformname, int value)
		{
			glUniform1i(GetUniformLocation(uniformname), 0);
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
	}
}


#include "shader.h"

namespace SJ_engine {
	namespace SJ_shader {
		shader::shader(Cl_window* obj)
		{
			char InfoLog[1024];
			std::ifstream file;
			std::string temp = "";
			std::string srcstr = "";
			//vertex shader
			file.open("resources/Shaders/basic_shaders/core_vs.shader");
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
			file.open("resources/shaders/basic_shaders/core_fs.shader");
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
			x_Shader_Program = createprogram(VertexShader, FragmentShader);
			UseShaderProgram(obj);
			//model matrix
			unsigned int model_loc;
			model = glm::translate(model, glm::vec3(0.f, 0.f, -1.f));
			model = glm::rotate(model, 45.f, glm::vec3(1.f, 0.f, 0.f));
			model = glm::rotate(model, 45.f, glm::vec3(0.f, 1.f, 0.f));
			model = glm::rotate(model, 0.f, glm::vec3(0.f, 0.f, 1.f));
			model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
			model_loc = glGetUniformLocation(x_Shader_Program, "u_model");
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
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

		void shader::Color_RotateIt(Cl_window* obj)
		{
			x_ColorShiftKey = obj->ColorShift;
			int location = glGetUniformLocation(x_Shader_Program, "uColor");
			//red channel shift
			int locshader = glGetUniformLocation(x_Shader_Program, "shader");
			if (x_ColorShiftKey)
			{
				glUniform1i(locshader, 1);
				if (r > 1.f)
				{
					inc = -0.007f;
				}
				else if (r < 0.0f)
				{
					inc = 0.007f;
				}
				r += inc;
			}
			else
			{
				glUniform1i(locshader,0);
			}
			glUniform4f(location, r, g, b, a);

		}
		void shader::UseShaderProgram(Cl_window* obj)
		{
			glUseProgram(x_Shader_Program);
		}

		void shader::shaderdestroy()
		{
			//Deleting shader program
			glDeleteProgram(x_Shader_Program);
		}
	}
}


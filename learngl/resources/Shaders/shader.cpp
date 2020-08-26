#include "shader.h"
namespace SJ_engine {
	namespace SJ_shader {
		//Color Shifting algo
		void shader::ColorIt(float r, float g, float b, float a)
		{
			
			int location = glGetUniformLocation(x_Shader_Program, "uColor");
			glUniform4f(location, r, g, b, a);
		}
		shader::shader()
		{
			char InfoLog[1024];
			std::ifstream file;
			std::string temp = "";
			std::string srcstr = "";
			//vertex shader
			file.open("resources/shaders/basic_shaders/core_vs.shader");
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
			glUseProgram(x_Shader_Program);
		}

		void shader::shaderdestroy()
		{
			//Deleting shader program
			glDeleteProgram(x_Shader_Program);
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
			return program;
		}

		void shader::GenBindData()
		{
			//shading positions and indices
			float positions[] =
			{
				-0.2f,0,0,//0
				0.2f,0.2f,0,//1
				0.2f,0,0,//2
				-0.2f,0.2f,0//3
			};
			unsigned int indices[] =
			{
				0,1,2,
				0,3,1
			};
			//buffers for positions
			unsigned int buffers;
			glGenBuffers(1, &buffers);
			glBindBuffer(GL_ARRAY_BUFFER, buffers);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			//vertex attributes enble and pointing them
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
			//index buffer
			//it can manage buffer data like Duplicate vertices 
			unsigned int indexbufferobj;
			glGenBuffers(1, &indexbufferobj);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferobj);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

	}
}


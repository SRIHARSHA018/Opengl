#pragma once
#include"src/graphics/Cl_window.h"
//CLASS for shader
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program;
			float r = 0.3f, g = 0.3f, b = 0.2f, a = 1.0f;
			float inc = 0.005f;
			bool x_ColorShiftKey = true;
		public:
			shader();
			glm::mat4 model = glm::mat4(1.f);
			glm::mat4 view = glm::mat4(1.f);
			glm::mat4 Projection = glm::mat4(1.f);
			unsigned int Get_shader_program(){	return x_Shader_Program; }
			void Color_RotateIt(Cl_window* obj);
			void GenBindData();
			void shaderdestroy();
			void UseShaderProgram(Cl_window* obj);
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);

		};
	}
}




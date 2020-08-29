#pragma once
#include"src/dependencies.h"
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
			void ColorIt(Cl_window* obj);
			void GenBindData();
			void shaderdestroy();
			void UseShaderProgram();
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);

		};
	}
}




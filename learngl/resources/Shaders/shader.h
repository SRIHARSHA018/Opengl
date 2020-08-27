#pragma once
#include"src/dependencies.h"
//CLASS for shader
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program;
			float r=0.3f, g=0.3f, b=0.2f,a=1.0f;
			float inc=0.005f;
		public:
			shader();
			void GenBindData();
			void shaderdestroy();
			void UseShaderProgram();
			void ColorIt();
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);
		};
	}
}




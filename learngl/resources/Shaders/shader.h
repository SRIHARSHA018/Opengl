#pragma once
#include"src/dependencies.h"
//CLASS for shader
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program;
			float r;
			float g;
			float b;
			float a;
		public:
			void ColorIt(float r,float g,float b,float a);
			shader();
			void shaderdestroy();
			unsigned int get_Program_Shader()
			{
				return x_Shader_Program;
			}
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);
			void GenBindData();
		};
	}
}




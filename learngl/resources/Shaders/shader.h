#pragma once
#include"src/dependencies.h"
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program;
		public:
			shader();
			void shaderdestroy();
			unsigned int get_Program_Shader()
			{
				return x_Shader_Program;
			}
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);
		};
	}
}




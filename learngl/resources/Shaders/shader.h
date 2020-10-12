#pragma once
#include<src/graphics/Cl_window.h>
#include"resources/textures/texture.h"
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
			shader(Cl_window* obj);
			glm::mat4 model = glm::mat4(1.f);
			glm::mat4 view = glm::mat4(1.f);
			glm::mat4 Projection = glm::mat4(1.f);
			unsigned int Get_shader_program(){	return x_Shader_Program; }
			void Color_RotateIt(Cl_window* obj);

			void GenBindData()
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
				glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,5*sizeof(float) , 0);
				//index buffer
				//it can manage buffer data like Duplicate vertices 
				unsigned int indexbufferobj;
				glGenBuffers(1, &indexbufferobj);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferobj);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
				//texturebind
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				glUniform1i(glGetUniformLocation(x_Shader_Program, "u_Texture"), 0);

			}
			void shaderdestroy();
			void UseShaderProgram(Cl_window* obj);
			unsigned int getviewmatrix_loc() { return glGetUniformLocation(x_Shader_Program, "u_View");}
			unsigned int getProjectionmatrix_loc() { return glGetUniformLocation(x_Shader_Program, "u_Projection"); }
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader);

		};
	}
}




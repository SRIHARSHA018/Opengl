#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<GLM/matrix.hpp>
#include"src/graphics/Cl_window.h"
#include"src/Shaders/shader.h"
namespace SJ_engine {
	namespace SJ_camera {
		class Camera 
		{
		private:
			glm::vec3 x_position;
			glm::vec3 x_up;
			glm::vec3 x_front;
			glm::vec3 x_WorldUp;
			glm::vec3 x_right;
			glm::vec3 x_initialPos;
			float x_yaw;
			float x_pitch;
			float x_movementspeed;
			float x_turnspeed;
			float x_DeltaTime=0;
			float x_lastTime=0;

		public:
			void reset_position();
			void Nav(Cl_window* obj,SJ_shader::shader* shaderObj);
			Camera(glm::vec3 intialPos,float movespeed,float turnspeed,float yaw,float pitch);
			~Camera();
			void keycontrol(Cl_window* obj, SJ_shader::shader* shaderObj);
			float get_deltaTime();
			glm::mat4 Cal_ViewMatrix();
			glm::mat4 Cal_projectionMatrix(float aspect);
			void update();
		};

	}
}


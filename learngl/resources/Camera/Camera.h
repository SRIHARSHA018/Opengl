#pragma once
#include<resources/Shaders/shader.h>
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
			void reset_position() {
				x_front = glm::vec3(0.f, 0.f, -1.f);
				x_position = x_initialPos;
				x_yaw = 0.f;
				x_pitch = 0.f;
			}
			void Nav(Cl_window* obj,SJ_shader::shader* shaderObj);
			Camera(glm::vec3 intialPos,float movespeed,float turnspeed,float yaw,float pitch);
			~Camera();
			void keycontrol(Cl_window* obj, SJ_shader::shader* shaderObj);
			float get_deltaTime() {
				float now =(float) glfwGetTime();
				x_DeltaTime = now - x_lastTime;
				x_lastTime = now;
				return x_DeltaTime;
			}
			glm::mat4 Cal_ViewMatrix()
			{
				return glm::lookAt(x_position, x_position + x_front, x_WorldUp);
			}
			glm::mat4 Cal_projectionMatrix(float aspect) { return glm::perspective(glm::radians(55.f),aspect,0.1f,100.f); }
			void update();
		};

	}
}


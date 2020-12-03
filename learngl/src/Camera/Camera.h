#pragma once
#include"GL/glew.h"
#include<GLM/glm.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<GLM/matrix.hpp>
#include<GLM/mat4x4.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include"src/graphics/Cl_window.h"
#include"src/Shaders/shader.h"
namespace SJ_engine {
	namespace SJ_camera {
		class Camera 
		{
		private:
			glm::mat4 x_ModelMatrix=glm::mat4(1.0f);
			glm::mat4 x_ViewMatrix= glm::mat4(1.0f);
			glm::vec3 x_camposition;
			glm::vec3 x_up;
			glm::vec3 x_front;
			glm::vec3 x_WorldUp;
			glm::vec3 x_right;
			glm::vec3 x_initialPos;
			float x_yaw=-90.f;
			float x_pitch;
			float x_movementspeed;
			float x_turnspeed;
			float x_DeltaTime=0.f;
			float x_lastTime=0.f;

		public:
			void reset_position();
			Camera(glm::vec3 intialPos,float movespeed,float turnspeed,float yaw,float pitch);
			~Camera();
			void keycontrol(Cl_window* obj, SJ_shader::shader* shaderObj);
			float get_deltaTime();
			void update();
			glm::mat4 getViewMatrix()const { return x_ViewMatrix; }
			glm::mat4 getModelMatrix()const { return x_ModelMatrix; }
			glm::vec3 getCamPosition() const { return x_camposition; }
			glm::vec3 getcamPos()const { return x_camposition; }
			
		};

	}
}


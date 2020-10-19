#include "Camera.h"
namespace SJ_engine {
	namespace SJ_camera {
		void Camera::reset_position()
		{
			x_front = glm::vec3(0.f, 0.f, -1.f);
			x_camposition = x_initialPos;
			x_yaw = -90.f;
			x_pitch = 0.f;
		}

		Camera::Camera(glm::vec3 intialPos, float movespeed, float turnspeed, float yaw, float pitch)
		{
			x_camposition = intialPos;
			x_initialPos = x_camposition;
			x_WorldUp = glm::vec3(0.f, 1.f, 0.f);
			x_front = glm::vec3(0.f, 0.f, -1.f);
			x_right = glm::normalize(glm::cross(x_WorldUp,x_front));
			x_up = glm::normalize(glm::cross(x_right, x_front));
			x_yaw = yaw;
			x_pitch = pitch;
			x_movementspeed = movespeed;
			x_turnspeed = turnspeed;	
			x_ModelMatrix = glm::translate(x_ModelMatrix, glm::vec3(0.f, 0.f, 0.f));
			x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
			x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
			x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
			x_ModelMatrix = glm::scale(x_ModelMatrix, glm::vec3(1.0f));
		}
		void Camera::update()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(x_yaw)) * cos(glm::radians(x_pitch));
			front.y = sin(glm::radians(x_pitch));
			front.z = sin(glm::radians(x_yaw)) * cos(glm::radians(x_pitch));
			x_front = glm::normalize(front);
			x_right = glm::normalize(glm::cross(x_WorldUp,x_front));
			x_up = glm::normalize(glm::cross(x_right, x_front));
			x_ViewMatrix = glm::lookAt(x_camposition, x_camposition + x_front, x_WorldUp);

		}
		Camera::~Camera()
		{

		}
		void Camera::keycontrol(Cl_window* obj,SJ_shader::shader* shaderObj)
		{
			float velocity = get_deltaTime() * x_movementspeed;
			if (obj->keys[GLFW_KEY_W] == true)
			{
				x_camposition += x_front * velocity;
			}
			if (obj->keys[GLFW_KEY_S] == true)
			{
				x_camposition -= x_front * velocity;
			}
			if (obj->keys[GLFW_KEY_A] == true)
			{
				x_camposition += x_right * velocity;
			}
			if (obj->keys[GLFW_KEY_D] == true)
			{
				x_camposition -= x_right * velocity;
			}
			if (obj->keys[GLFW_KEY_W] || obj->keys[GLFW_KEY_S] || obj->keys[GLFW_KEY_A] || obj->keys[GLFW_KEY_D] || obj->keys[GLFW_KEY_LEFT_ALT])
			{
				if (obj->mousebuttons[GLFW_MOUSE_BUTTON_LEFT] == true)
				{
					obj->xChange *= x_turnspeed;
					obj->yChange *= x_turnspeed;
					x_yaw += (float)obj->xChange;
					x_pitch += (float)obj->yChange;	
					if (x_pitch > 89.f)
					{
						x_pitch = 89.f;
					}
					if (x_pitch < -89.f)
					{
						x_pitch = -89.f;
					}
					update();
				}

			}
			if (obj->keys[GLFW_KEY_F] == true)
			{
				reset_position();
				update();
			}
		}

		float Camera::get_deltaTime()
		{
			float now = (float)glfwGetTime();
			x_DeltaTime = now - x_lastTime;
			x_lastTime = now;
			return x_DeltaTime;
		}
	}
}

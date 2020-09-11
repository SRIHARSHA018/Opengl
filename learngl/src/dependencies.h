#pragma once
#define PI (3.14)
#define Matrix_view(view) (	std::cout << view[0][0] << "\t" << view[0][1] << "\t" << view[0][2] << std::endl<< view[1][0] << "\t" << view[1][1] << "\t" << view[1][2] << std::endl<< view[2][0] << "\t" << view[2][1] << "\t" << view[2][2] << std::endl)
#include<GL/glew.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLM/mat4x4.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include"GLFW/glfw3.h"

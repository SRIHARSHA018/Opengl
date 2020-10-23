#pragma once
#include "Light.h"
class PointLight :
    public Light
{
private:
    glm::vec3 x_Position;
public:
    PointLight();
    ~PointLight(){}
   PointLight(float ambientintensity, float red, float green, float blue,
        float diffintensity, glm::vec3 direction, float specular_intensity, float specular_pow);
   glm::vec3 GetPointLightPosition() { return x_Position; }
   void SetPointLightPos(float x, float y, float z);
};


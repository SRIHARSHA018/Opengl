#pragma once
#include "Light.h"

class DirectionalLight :
    public Light
{
private:

    glm::vec3 x_LightDirection;


public:
    glm::vec3 GetLightDirection() { return x_LightDirection; }
    DirectionalLight();
    ~DirectionalLight(){}
    DirectionalLight(float ambientintensity, float red, float green, float blue,
        float diffintensity, glm::vec3 diffusedirection);
    void SetLightDirection(float x, float y, float z);
};


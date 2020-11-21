#version 460 core

out vec4 FragColor;

uniform vec3 u_lightColor;
uniform float u_intensity;

void main()
{
    FragColor = vec4(vec3(1.f),1.0f); // set alle 4 vector values to 1.0
}
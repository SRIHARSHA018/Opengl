#version 460 core

out vec4 FragColor;

uniform vec3 u_lightColor;
uniform float u_intensity;

void main()
{
    FragColor = vec4(u_lightColor*u_intensity,1.0f); // set alle 4 vector values to 1.0
}
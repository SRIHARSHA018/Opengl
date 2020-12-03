#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<string>
#include<vector>
struct Vertex
{
	glm::vec3 vertexPositions;
	glm::vec2 TextureCoordinates;
	glm::vec3 vertexNormals;
};
struct texture
{
	unsigned int id;
	std::string type;
	std::string path;
};
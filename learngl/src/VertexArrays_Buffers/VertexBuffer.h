#include<GL/glew.h>
#include<GLM/glm.hpp>
struct Vertex
{
	glm::vec3 vertexPositions;
	glm::vec2 TextureCoordinates;
	glm::vec3 vertexNormals;
};
class VertexBuffer
{
private:
	unsigned int x_id;
public:
	VertexBuffer(){}
	~VertexBuffer();
	void GenBuffer(const void* data, unsigned int& size);
	void Bind() const;
	void UnBind() const;
};
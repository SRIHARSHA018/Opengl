#include<iostream>
#include"src/Shaders/shader.h"

class Mesh
{

private:

	//vertex attributes holders
	std::vector<Vertex> x_vertices;
	std::vector<unsigned int> x_indices;
	std::vector<texture> x_textures;

	unsigned int x_vbo,x_vao,x_ebo;

	void x_EnableVertexAttrib();
	void x_setup_mesh();
	void x_InitModelMatrix();
	glm::mat4 x_ModelMatrix=glm::mat4(1.0f);
public:
	glm::mat4 GetModelMatrix()const { return x_ModelMatrix; }
	enum PrimitiveType
	{
		Cube,
		Plane
	};
	Mesh(){}
	~Mesh();
	Mesh(PrimitiveType primitive);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void DrawMesh(SJ_engine::SJ_shader::shader* obj);

	void SetTransformations(const glm::vec3& position,const glm::vec3& rotation,const glm::vec3& scale);

	void CreateCube();
	void CreatePlane();

	void BindMesh();



};

#include<iostream>
#include"src/Materials/Material.h"
class Mesh :public VertexBuffer
{
private:
	unsigned int x_vao;
	void x_setup_mesh(const void* data, unsigned int size);
	void x_InitModelMatrix();
	glm::mat4 x_ModelMatrix;
public:
	glm::mat4 GetModelMatrix() { return x_ModelMatrix; }
	Mesh(int primitive);
	void DrawMesh(SJ_engine::SJ_shader::shader* obj);
	void CreateCube();
	void CreatePlane();
	void SetTranslation(const glm::vec3& position);
	void BindMesh();
	~Mesh() {}
};
#include<iostream>
#include"src/Materials/Material.h"
class Mesh :public VertexBuffer
{
private:

	void x_setup_mesh(const void* data,unsigned int size);
public:
	Mesh(int primitive);
	void DrawMesh(SJ_engine::SJ_shader::shader* obj,Material* mat_Obj);
	void CreateCube();
	~Mesh(){}
};
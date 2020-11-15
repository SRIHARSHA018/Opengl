#include "Mesh.h"

Mesh::Mesh(int primitive)
{
	switch (primitive)
	{
	case 0:
		CreateCube();
	}
}

void Mesh::CreateCube()
{
	float vertexattribs[] =
	{

		//cube2
		 //back face
		 -0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,0.f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,1.0f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,1.0f,	 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.f,1.0f,    0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f,  0.0f, -1.0f,
		//front face
		-0.5f, -0.5f, 0.5f,		0.f,0.f,	 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f,0.f,	 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		1.f,1.f,	 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		1.f,1.f,	 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		0.f,1.f,	 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.f,0.f,	 0.0f,  0.0f, 1.0f,
		//left face									 
		-0.5f,  0.5f,  0.5f,	0.f,0.f,	 -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f,0.f,	 -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	1.f,1.f,	 -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	1.f,1.f,	 -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.f,1.f,	 -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.f,0.f,	 -1.0f,  0.0f,  0.0f,
		//RIGHT FACE									 
		  0.5f,  0.5f,  0.5f,	0.f,0.f,     1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,	1.0f,0.f,    1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,	1.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,	1.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,	0.f,1.f,     1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,	0.f,0.f,     1.0f,  0.0f,  0.0f,
	  //bottom face								 
		-0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,0.f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.f,1.f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.f,1.f,	 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.f,1.f,	 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.f,0.f,	 0.0f, -1.0f,  0.0f,
		//top face
		-0.5f,  0.5f, -0.5f,	0.f,0.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,0.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.f,1.f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.f,1.f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.f,1.f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.f,0.f,	 0.0f,  1.0f,  0.0f
	};
	x_setup_mesh(&vertexattribs,sizeof(vertexattribs));
}
void Mesh::x_setup_mesh(const void* data,unsigned int size)
{
	
	GenBuffer(data, size);
	//VertexPositions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//TextureCoordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinates));
	//VertexNormals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertexNormals));

	UnBind();
}
void Mesh::DrawMesh(SJ_engine::SJ_shader::shader* obj, Material* mat_Obj)
{
	obj->UseShaderProgram();
	mat_Obj->AssignMaterial(obj);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
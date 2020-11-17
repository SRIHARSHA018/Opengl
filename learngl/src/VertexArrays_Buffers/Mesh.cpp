#include "Mesh.h"

Mesh::Mesh(int primitive)
{
	x_InitModelMatrix();
	switch (primitive)
	{
	case 0:
		CreateCube();
		break;
	case 1:
		CreatePlane();
		break;
	}
}


void Mesh::x_setup_mesh(const void* data,unsigned int size)
{
	
	GenBuffer(data, size);
	glCreateVertexArrays(1, &x_vao);
	glBindVertexArray(x_vao);

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
	glBindVertexArray(0);
}
void Mesh::x_InitModelMatrix()
{
	x_ModelMatrix = glm::mat4(1.f);
	x_ModelMatrix = glm::translate(x_ModelMatrix, glm::vec3(0.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
	x_ModelMatrix = glm::scale(x_ModelMatrix, glm::vec3(1.0f));
}
void Mesh::DrawMesh(SJ_engine::SJ_shader::shader* obj, Material* mat_Obj)
{
	obj->UseShaderProgram();
	Bind();
	glBindVertexArray(this->x_vao);
	mat_Obj->AssignMaterial(obj);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Mesh::CreateCube()
{
	float cubepoints[] =
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
	x_setup_mesh(&cubepoints,sizeof(cubepoints));
}
void Mesh::CreatePlane()
{
	float planepoints[] =
	{
		//left triangle
		//vertex positions     texture coordinates         normals
		-10.f,-1.f,-10.f,      0.f,0.f,                    0.f,1.f,0.f,
		 10.f,-1.f,-10.f,      1.f,0.f,                    0.f,1.f,0.f,
		 10.f,-1.f,10.f,       1.f,1.f,                    0.f,1.f,0.f,
		 //right triangle
		-10.f,-1.f,-10.f,      0.f,0.f,                    0.f,1.f,0.f,
		 10.f,-1.f,10.f,       1.f,1.f,                    0.f,1.f,0.f,
		 -10.f,-1.f,10.f,      0.f,1.f,                    0.f,1.f,0.f,
	};
	 x_setup_mesh(&planepoints,sizeof(planepoints));
}

void Mesh::SetTranslation(const glm::vec3& position)
{
	x_ModelMatrix = glm::translate(x_ModelMatrix,position);
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
	x_ModelMatrix = glm::scale(x_ModelMatrix, glm::vec3(1.0f));
}

void Mesh::BindMesh()
{
	Bind();
	glBindVertexArray(x_vao);
}
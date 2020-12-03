#include "Model.h"



Model::Model(const std::string& path)
	:x_path(path)
{
	x_LoadModel();
}

void Model::x_LoadModel()
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(x_path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_JoinIdenticalVertices);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::scene file is empty" << std::endl;
		return;
	}
	x_directory = x_path.substr(0, x_path.find_last_of('/'));
	this->x_processNode(scene->mRootNode, scene);
}

void Model::x_processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->x_meshes.push_back(this->x_ProcessMesh(mesh,scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->x_processNode(node->mChildren[i], scene);
	}
}

Mesh Model::x_ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.vertexPositions = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.vertexNormals = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TextureCoordinates = vec;
		}
		else
			vertex.TextureCoordinates = glm::vec2(0.0f, 0.0f);

		x_vertices.push_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			x_indices.push_back(face.mIndices[j]);
		}
	}
	return Mesh(x_vertices, x_indices);
}


void Model::DrawModel(SJ_engine::SJ_shader::shader* obj)
{
	for (unsigned int i = 0; i < x_meshes.size(); i++)
	{
		x_meshes[i].DrawMesh(obj);
		obj->SetUniformMatrix4f("u_model", 1, x_meshes[i].GetModelMatrix());
	}
	
}

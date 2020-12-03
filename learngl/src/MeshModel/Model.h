#pragma once
#include "src/MeshModel/Mesh.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<vector>
class Model
{
private:
	std::vector<Vertex> x_vertices;
	std::vector<unsigned int> x_indices;
	std::vector<texture> x_textures;
	std::string x_path;
	std::string x_directory;
	std::vector<Mesh> x_meshes;
	void x_LoadModel();
	void x_processNode(aiNode* node, const aiScene* scene);
	Mesh x_ProcessMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	//	std::string typeName);

public:
	void DrawModel(SJ_engine::SJ_shader::shader* obj);
	Model(const std::string& path);
	~Model(){}
};


#pragma once
#include "src/MeshModel/Mesh.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<vector>

class Model
{
private:
	std::string x_path;
	std::string x_directory;
	std::vector<Mesh> x_meshes;
	std::vector<texture> x_textures;
	std::vector<BasicMaterial> x_ModelMaterial;
	void x_LoadModel();
	void x_processNode(aiNode* node, const aiScene* scene);
	Mesh x_ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<texture> x_LoadMaterialTextures(aiMaterial* mat,
		aiTextureType type, std::string typeName);
	unsigned int x_TextureFromFile(const char* path, const std::string& directory, bool gamma);
public:
	void DrawModel(SJ_engine::SJ_shader::shader* obj,BasicMaterial* baseMat=nullptr, StandardMaterial* standMat = nullptr);
	Model(const std::string& path);
	void MaterialDispatcher(std::vector<texture>* obj);
	~Model(){}
};


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
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;
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

		vertices.push_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// 1. diffuse maps
		std::vector<texture> diffuseMaps = x_LoadMaterialTextures(material, aiTextureType_DIFFUSE, "u_material.base.diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<texture> specularMaps = x_LoadMaterialTextures(material, aiTextureType_SPECULAR, "u_material.base.specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	MaterialDispatcher(&textures);
	return Mesh(vertices, indices,textures);
}
void Model::MaterialDispatcher(std::vector<texture>* obj)
{

}


std::vector<texture> Model::x_LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		texture texture;
		texture.id = x_TextureFromFile(str.C_Str(), x_directory,0);
		texture.type = typeName;
		texture.path = str.C_Str();
		textures.push_back(texture);
	}
	return textures;
}


unsigned int Model::x_TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Model::DrawModel(SJ_engine::SJ_shader::shader* obj, BasicMaterial* baseMat, StandardMaterial* standMat)
{
	for (unsigned int i = 0; i < x_meshes.size(); i++)
	{

		x_meshes[i].DrawMesh(obj, baseMat, standMat);
	}
}
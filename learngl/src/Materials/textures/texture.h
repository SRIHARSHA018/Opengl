#pragma once
#include<string>
#include<GL/glew.h>
#include"resources/vendor/STB_image/stb_image.h"

class Texture
{
private:
	unsigned int x_ID;
	std::string x_FilePath;
	unsigned char* x_Local_Buffers;
	std::string x_texture_type;
	int x_Width, x_Height, x_BPP;
	unsigned int x_Slot;
public:
	Texture(){}
	Texture(const std::string& path,unsigned int slot);
	void CreateSampler(const std::string& path,unsigned int& slot);
	~Texture();

	std::string GetTextureType() { return x_texture_type; }
	unsigned int GetTextureID() { return x_ID; }
	unsigned int GetTextureSlot()const { return x_Slot; }
	std::string GetTextureFilePath() { return x_FilePath; }

	int GetWidth()const { return x_Width; }
	int GetHeigth()const { return x_Height; }

	void Bind() const;
	void UnBind() const;
};
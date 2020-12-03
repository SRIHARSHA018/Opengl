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
	int x_Width, x_Height, x_BPP;
	unsigned int x_Slot;
public:
	Texture(){}
	Texture(const std::string& path,unsigned int slot);
	void CreateSampler(const std::string& path,unsigned int& slot);
	~Texture();
	void Bind() const;
	void UnBind() const;
	unsigned int GetTextureSlot()const { return x_Slot; }
	int GetWidth()const { return x_Width; }
	int GetHeigth()const { return x_Height; }
};
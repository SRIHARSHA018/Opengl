#pragma once
#include<string>
#include<GL/glew.h>


class Texture
{
private:
	unsigned int x_ID;
	std::string x_FilePath;
	unsigned char* x_Local_Buffers;
	int x_Width, x_Height, x_BPP;
	unsigned int x_Slot ;
public:
	Texture(const std::string& path, unsigned int slot);
	~Texture();
	void Bind() const;
	void UnBind() const;
	unsigned int GetTextureSlot() { return x_Slot; }
	int GetWidth() { return x_Width; }
	int GetHeigth() { return x_Height; }
};
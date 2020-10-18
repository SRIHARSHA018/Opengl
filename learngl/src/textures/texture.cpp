#include"texture.h"
#include"resources/vendor/STB_image/stb_image.h"
Texture::Texture(const std::string& path)
	:x_ID(0),x_FilePath(path),x_Local_Buffers(nullptr),x_Width(0),x_Height(0),x_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	x_Local_Buffers = stbi_load(path.c_str(), &x_Width, &x_Height,&x_BPP,4);
	glGenTextures(1, &x_ID);
	glBindTexture(GL_TEXTURE_2D, x_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x_Width, x_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, x_Local_Buffers);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	if (x_Local_Buffers)
	{
		stbi_image_free(x_Local_Buffers);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &x_ID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE_2D + slot);
	glBindTexture(GL_TEXTURE_2D, x_ID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

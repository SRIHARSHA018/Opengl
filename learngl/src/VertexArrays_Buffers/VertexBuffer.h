#pragma once
#include<GL/glew.h>
class VertexBuffer
{

private:
	unsigned int x_VertexBuffer_ID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void BindBuffer() const;
	void UnBindBuffer() const;
};
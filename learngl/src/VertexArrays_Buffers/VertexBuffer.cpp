#include"VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &x_VertexBuffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, x_VertexBuffer_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &x_VertexBuffer_ID);
}

void VertexBuffer::BindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, x_VertexBuffer_ID);
}

void VertexBuffer::UnBindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, x_VertexBuffer_ID);
}

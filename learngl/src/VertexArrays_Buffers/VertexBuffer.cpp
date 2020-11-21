#include "VertexBuffer.h"

void VertexBuffer::GenBuffer(const void* data, unsigned int& size)
{
	glGenBuffers(1, &x_id);
	glBindBuffer(GL_ARRAY_BUFFER, x_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &x_id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, x_id);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include"IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:x_Count(count)
{
	glGenBuffers(1, &x_IndexBuffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, x_IndexBuffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &x_IndexBuffer_ID);
}

void IndexBuffer::BindBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, x_IndexBuffer_ID);
}

void IndexBuffer::UnBindBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, x_IndexBuffer_ID);
}

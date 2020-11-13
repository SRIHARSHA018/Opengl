
#pragma once
#include<GL/glew.h>
class IndexBuffer
{

private:
	unsigned int x_IndexBuffer_ID;
	unsigned int x_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void BindBuffer();
	void UnBindBuffer();

	inline unsigned int GetCount() const { return x_Count; }
};
#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
{
	GLCall(glGenBuffers(1, &_id));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &_id));
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
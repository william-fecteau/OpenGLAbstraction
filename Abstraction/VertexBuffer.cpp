#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &_id));
}

void VertexBuffer::SetData(const void* data, unsigned int size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &_id));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
}
 
void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
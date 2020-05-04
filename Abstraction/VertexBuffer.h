#pragma once

#include <glad/glad.h>

/**
*	A vertex buffer is an array that contains data stored with a certain layout (VertexBufferLayout)
*/
class VertexBuffer
{
private:
	//Id in the OpenGL context
	unsigned int _id;

public:
	/**
	*	Create a vertex buffer in the OpenGL context using an array
	*
	*	@param data Pointer to the buffer data array
	*	@param size Total size (in bytes) of the buffer data array
	*/
	VertexBuffer(const void* data, unsigned int size);
	
	/**
	*	Delete this vertex buffer from OpenGL context
	*/
	~VertexBuffer();

	/**
	*	Binds this vertex buffer as a GL_ARRAY_BUFFER to the OpenGL context
	*	PS: It doesn't unbind the other type of buffer, ex: GL_ELEMENT_ARRAY
	*/
	void Bind() const;

	/**
	*	Binds nothing as a GL_ARRAY_BUFFER to the OpenGL context
	*	PS: It doesn't unbind the other type of buffer, ex: GL_ELEMENT_ARRAY
	*/
	void Unbind() const;
};
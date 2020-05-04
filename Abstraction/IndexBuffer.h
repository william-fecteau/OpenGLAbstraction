#pragma once

#include <glad/glad.h>

/**
*	An index buffer is an array of index that points to data in the currently bound vertex buffer
*	It is used with the glDrawElements(...); draw call
*/
class IndexBuffer
{
private:
	//Id in the OpenGL context
	unsigned int _id;

public:
	/**
	*	Create an index buffer in the OpenGL context using an array of element (or index)
	*
	*	@param data Pointer to the array of element (or index)
	*	@param count Number of element in the array
	*/
	IndexBuffer(const unsigned int* data, unsigned int count);

	/**
	*	Delete this index buffer from the OpenGL context
	*/
	~IndexBuffer();

	/**
	*	Binds this index buffer as a GL_ELEMENT_ARRAY_BUFFER to the OpenGL context
	*	PS: It doesn't unbind the other type of buffer, ex: GL_ARRAY_BUFFER
	*/
	void Bind() const;

	/**
	*	Binds nothing as a GL_ELEMENT_ARRAY_BUFFER to the OpenGL context
	*	PS: It doesn't unbind the other type of buffer, ex: GL_ARRAY_BUFFER
	*/
	void Unbind() const;
};
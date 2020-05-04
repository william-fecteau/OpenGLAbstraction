#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
*	A vertex array is an array of vertex buffer.
*	It can be drawn with glDrawArray(...);
*/
class VertexArray
{
private:
	//Id in the OpenGL context
	unsigned int _id;

public:
	/**
	*	Create an empty vertex array in the OpenGL context
	*/
	VertexArray();

	/**
	*	Delete this vertex array from the OpenGL context
	*/
	~VertexArray();

	/**
	*	Add a vertex buffer to this vertex array by specifying the layout of the vertex buffer data
	*
	*	@param vb Vertex buffer to bind to this vertex array
	*	@param layout Layout of the data int the vertex buffer
	*/
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

	/**
	*	Binds this vertex array the OpenGL context
	*/
	void Bind() const;

	/**
	*	Binds nothing to the OpenGL context
	*/
	void Unbind() const;
};
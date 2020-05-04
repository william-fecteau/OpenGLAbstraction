#pragma once
#include <vector>

/**
*	One element in a vertex buffer.
*	Example: position is an element composed of 3 float (x,y,z)
*/
struct VertexBufferElement
{
	//OpenGL type of the data (GL_FLOAT, GL_INT, etc.)
	unsigned int type;
	//Count of the type
	unsigned int count;
	//If it is normalized (GL_TRUE or GL_FALSE)
	unsigned char normalized;

	/**
	*	Returns the size in bytes of an OpenGL type
	*
	*	@param OpenGL type (GL_GLOAT, GL_BYTE, etc.)
	*	@return Size in bytes of an OpenGL type
	*/
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_BYTE:
				return 1;
		}

		return 0;
	}
};


/**
*	Layout of the data stored in a vertex buffer
*/
class VertexBufferLayout
{
private:
	//Vector of elements in a vertex buffer
	std::vector<VertexBufferElement> _elements;
	//Number of bytes to jump to get to the next element
	unsigned int _stride;

public:
	/**
	*	Create an empty vertex buffer layout
	*/
	VertexBufferLayout() : _stride(0) {}

	/**
	*	Pushes some data in the layout. Implemented with a template that allow for multiple type specialization
	*
	*	@param count Count of the type to add to the layout (Not in bytes)
	*/
	template<typename T>
	void Push(unsigned int count)
	{

	}
	
	template<>
	void Push<float>(unsigned int count)
	{
		_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		_elements.push_back({ GL_BYTE, count, GL_TRUE });
		_stride += count * VertexBufferElement::GetSizeOfType(GL_BYTE);
	}

	/**
	*	Getter for all the elements
	*/
	inline const std::vector<VertexBufferElement> GetElements() const { return _elements; }

	/**
	*	Getter for the stride
	*/
	inline unsigned int GetStride() const { return _stride; }
};
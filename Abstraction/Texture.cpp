#include "Texture.h"
#include "Renderer.h"

Texture::Texture(Image& img)
{
	GLCall(glGenTextures(1, &_id));

	Bind();	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int colorFormat = GL_RGB;
	if (img.GetTransparency())
	{
		colorFormat = GL_RGBA;
	}

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.GetWidth(), img.GetHeight(), 0, colorFormat, GL_UNSIGNED_BYTE, img.GetData()));
	
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
}


void Texture::Bind(unsigned int activeTexture) const
{
	if (activeTexture > 15)
	{
		//Error handling
	}

	GLCall(glActiveTexture(GL_TEXTURE0 + activeTexture));
	GLCall(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
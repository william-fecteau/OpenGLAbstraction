#pragma once

#include "Image.h"

class Texture
{
private:
	unsigned int _id;

public:
	Texture(Image& img);

	void Bind(unsigned int activeTexture = 0) const;
	void Unbind() const;
};
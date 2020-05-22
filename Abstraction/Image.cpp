#include "Image.h"
#include <stb_image/stb_image.h>

Image::Image(const std::string& path, const bool transparency)
{
	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(path.c_str(), &_width, &_height, &_nbChannel, 0);
	if (!_data)
	{
		//TODO: Error handling
	}

	_transparency = transparency;
}

Image::~Image()
{
	stbi_image_free(_data);
}
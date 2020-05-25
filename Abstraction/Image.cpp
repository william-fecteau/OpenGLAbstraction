#include "Image.h"
#include <stb_image/stb_image.h>

Image::Image(const bool transparency)
{
	_transparency = transparency;
	_width = 0;
	_height = 0;
	_nbChannel = 0;
	_data = NULL;
}

void Image::LoadResource()
{
	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(_path->c_str(), &_width, &_height, &_nbChannel, 0);
	if (!_data)
	{
		//TODO: Error handling
	}
}

void Image::UnloadResource()
{
	stbi_image_free(_data);
}

Image::~Image()
{
	if(_data) UnloadResource();
}
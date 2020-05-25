#pragma once

#include <string>
#include "Resource.h"

class Image : public Resource
{
private:
	unsigned char* _data;
	int _width;
	int _height;
	int _nbChannel;
	bool _transparency;

public:
	Image(const bool transparency = false);
	~Image();

	void LoadResource();
	void UnloadResource();

	const unsigned char* GetData() const { return _data; };
	const int GetWidth() const { return _width; };
	const int GetHeight() const { return _height; };
	const int GetNbChannel() const { return _nbChannel; };
	const bool GetTransparency() const { return _transparency; }
};
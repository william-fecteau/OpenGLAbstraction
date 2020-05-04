#pragma once

#include "string"

class Image
{
private:
	unsigned char* _data;
	int _width;
	int _height;
	int _nbChannel;
	bool _transparency;

public:
	Image(const std::string& path, const bool transparency = false);
	~Image();

	const unsigned char* GetData() const { return _data; };
	const int GetWidth() const { return _width; };
	const int GetHeight() const { return _height; };
	const int GetNbChannel() const { return _nbChannel; };
	const bool GetTransparency() const { return _transparency; }
};
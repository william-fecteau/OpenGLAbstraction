#pragma once

#include <string>

class Resource
{
protected:
	unsigned int _resourceId;
	std::string* _path;

public:
	virtual void LoadResource() = 0;
	virtual void UnloadResource() = 0;

	const unsigned int GetResourceId() const { return _resourceId; };
	void SetResourceId(const unsigned int id) { _resourceId = id; };

	const std::string* GetPath() const { return _path; };
	void SetPath(std::string* path) { _path = path; };
};

#pragma once

#include <string>

class Resource
{
protected:
	unsigned int _resourceId;
	bool _loaded;
	std::string _path;

public:
	Resource() : _loaded(false), _resourceId(0), _path("") {}
	virtual ~Resource() {}

	virtual void LoadResource() { _loaded = true; };
	virtual void UnloadResource() { _loaded = false; };

	const unsigned int GetResourceId() const { return _resourceId; };
	void SetResourceId(const unsigned int id) { _resourceId = id; };

	const std::string GetResourcePath() const { return _path; };
	void SetResourcePath(const std::string& path) { _path = path; };
};

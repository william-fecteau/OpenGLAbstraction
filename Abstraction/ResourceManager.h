#pragma once

#include <unordered_map>
#include <string>
#include "Resource.h"

class ResourceManager
{
private:
	std::unordered_map< std::string, Resource*> _resourcesMap;
	static ResourceManager* g_instance;
	
	//Empêche la construction d'un objet -> on doit passer par GetInstance()
	ResourceManager();
public:
	~ResourceManager();

	static ResourceManager* GetInstance();

	void AddResource(Resource* resource, const std::string& name, const std::string& path);
	
	template <typename T>
	void RemoveResource(const std::string& name)
	{
		if (_resourcesMap.find(name) == _resourcesMap.end())
		{
			//Not found -> Error handling
		}
		else
		{
			T* res = dynamic_cast<T*>(_resourcesMap.find(name)->second);
			if (res != nullptr)
			{
				res->UnloadResource();
				delete res;
			}

			_resourcesMap.erase(name);
		}
	}

	template <typename T>
	T* GetResource(const std::string& name)
	{
		if (_resourcesMap.find(name) == _resourcesMap.end())
		{
			//TODO: ERROR handling (not found)   
			return nullptr;
		}
		else
		{
			T* resource = dynamic_cast<T*>(_resourcesMap.find(name)->second);

			if (resource == nullptr) 
			{

			}	

			return resource;
		}

	}
};
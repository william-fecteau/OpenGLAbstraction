#include "ResourceManager.h"

#include <utility>

ResourceManager* ResourceManager::g_instance = nullptr;

ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager()
{
    std::unordered_map<std::string, Resource*>::iterator itr;

    for (itr = _resourcesMap.begin(); itr != _resourcesMap.end(); itr++)
    {
        itr->second->UnloadResource();
        delete itr->second;
    }

    delete g_instance;
}

ResourceManager* ResourceManager::GetInstance()
{
    if (!g_instance) g_instance = new ResourceManager();
    return g_instance;
}

void ResourceManager::AddResource(Resource* resource, const std::string& name, const std::string& path)
{
	if (_resourcesMap.find(name) == _resourcesMap.end())
	{
		_resourcesMap[name] = resource;
        resource->SetResourceId(_resourcesMap.size());
        resource->SetResourcePath(path);
	}
	//else resource already exist -> error handling
}


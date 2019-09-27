#pragma once

#include <string>
#include <vector>
#include "PointerBag.h"
#include "Sprite.h"
//#include "SpriteResource.h"


#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager(PointerBag* pointerBag);
	~ResourceManager() {}

	//void Create() {}
	void Destroy() {}

	ResourceId AddResource(Resource::ResourceType type, std::string path);
	void RemoveResource(ResourceId id);
	Resource* GetResource(ResourceId id);

	void DoGarbageCollection();

private:
	PointerBag* pointerBag = nullptr;

	std::vector<Resource*> resources;
};

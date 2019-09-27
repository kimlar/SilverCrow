#pragma once

#include <iostream>

//#include "ResourceManager.h"
class ResourceManager;

using ResourceId = int;
using ResourceTypeId = int;

class Resource
{
	static ResourceId serial;

public:
	enum class ResourceType
	{
		Sprite = 0,
		Animation,
		Sound,
		Music,
		Map,
		//GameObject, // ???
		Count // Number of resource types
	};

	//Resource() : id(++serial), useGarbage(true) { }
	Resource() : id(++serial) { printf("Resource(): id=%d\n", id); }
	virtual ~Resource() { printf("~Resource()\n"); }

	virtual void GarbageCollection() = 0;
	virtual void Free() = 0;

	ResourceId GetResourceId() { return id; }
	ResourceTypeId GetResourceTypeId() { return typeId; }

private:
	ResourceId id;

protected:
	ResourceTypeId typeId;
	//bool useGarbage; // Set deletion mode to garbage collection instead of immediate
};

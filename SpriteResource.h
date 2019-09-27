#pragma once

#include <string>
#include "Sprite.h"
#include "Resource.h"
#include "PointerBag.h"

class SpriteResource : public Resource
{
	const ResourceTypeId _typeId = (ResourceTypeId)ResourceType::Sprite;

public:
	//SpriteResource(PointerBag* pointerBag, std::string path);
	SpriteResource(PointerBag* pointerBag);
	//virtual ~SpriteResource() { Free(); }
	virtual ~SpriteResource() { printf("~SpriteResource()\n"); }

	ResourceId Load(std::string path);
	void Unload();

	void GarbageCollection();
	void Free();

	int GetCount() { return count; }
	Sprite* GetSprite() { return sprite; }
	std::string GetPath();
	
private:
	PointerBag* pointerBag;

	Sprite* sprite;
	std::string path;
	int count; // count of usages of this (texture) resource
};

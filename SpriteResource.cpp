#include "SpriteResource.h"

//SpriteResource::SpriteResource(PointerBag* pointerBag, std::string path) : pointerBag(pointerBag) ,path(path)
SpriteResource::SpriteResource(PointerBag* pointerBag) : pointerBag(pointerBag), path(path)
{
	typeId = _typeId;
	//Load(path);
	printf("SpriteResource():\n");
}

ResourceId SpriteResource::Load(std::string path)
{
	++count;

	printf("Load: %d\n", count);

	if (sprite == nullptr)
	{
		this->path = path;
		sprite = new Sprite(pointerBag->GetRenderer());
		sprite->Load(path);

		printf("Loaded\n");
	}

	return GetResourceId();
}

void SpriteResource::Unload()
{
	--count;
	if (count < 0)
		count = 0;

	printf("Unload: %d\n", count);
	//if (count == 0 && !useGarbage)
	//	Free();
}

void SpriteResource::GarbageCollection()
{
	printf("GC: %d {\n", count);

	if (count == 0)
		Free();

	printf("GC: }\n");
}

void SpriteResource::Free()
{
	if (sprite)
	{
		sprite->Unload();
		delete sprite;
		sprite = nullptr;
		printf("Freed\n");
	}
}

std::string SpriteResource::GetPath()
{
	return path;
}

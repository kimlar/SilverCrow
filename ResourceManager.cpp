#include "ResourceManager.h"

#include "SpriteResource.h"

ResourceManager::ResourceManager(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	pointerBag->SetResourceManager(this);
}

ResourceId ResourceManager::AddResource(Resource::ResourceType type, std::string path)
{
	if (type == Resource::ResourceType::Sprite)
	{
		for (int i = 0; i < (int)resources.size(); i++)
		{
			if (resources[i]->GetResourceTypeId() == (ResourceTypeId)Resource::ResourceType::Sprite)
			{
				SpriteResource* loadedResource = static_cast<SpriteResource*>(resources[i]);
				if (loadedResource->GetPath() == path)
				{
					printf("AddResource: Loading old: %s\n", path.c_str());
					return loadedResource->Load(path);
				}
			}
		}
		SpriteResource* newResource = new SpriteResource(pointerBag);
		resources.push_back(newResource);
		printf("AddResource: Loading new: %s\n", path.c_str());
		return newResource->Load(path);
	}

	//..

	printf("AddResource: Crapped\n");

	return 0;
}

void ResourceManager::RemoveResource(ResourceId id)
{
	for (int i = 0; i < (int)resources.size(); i++)
	{
		if (resources[i]->GetResourceId() == id)
		{
			if (resources[i]->GetResourceTypeId() == (ResourceTypeId)Resource::ResourceType::Sprite)
			{
				printf("RemoveResource: id=%d\n", id);
				SpriteResource* tempResource = static_cast<SpriteResource*>(resources[i]);
				tempResource->Unload();
				//SpriteResource* tempResource = dynamic_cast<SpriteResource*>(resources[i]);
				//tempResource->Unload();
				//if (tempResource->GetCount() == 0)
				//{
				//	//resources.erase(resources.begin() + i);
				//}
				//resources[i]->Free();
				//resources.erase(resources.begin() + i);
				break;
			}
		}
	}
}

Resource* ResourceManager::GetResource(ResourceId id)
{
	for (int i = 0; i < (int)resources.size(); i++)
		if (resources[i]->GetResourceId() == id)
			return resources[i];

	return nullptr; // did not find any resources by that id
}

void ResourceManager::DoGarbageCollection()
{
	printf("Game::Destroy(): GC working..\n");
	std::vector<ResourceId> deleteId;

	for (int i = 0; i < (int)resources.size(); i++)
	{
		resources[i]->GarbageCollection();
		if (resources[i]->GetResourceTypeId() == (ResourceTypeId)Resource::ResourceType::Sprite)
		{
			SpriteResource* sr = static_cast<SpriteResource*>(resources[i]);
			if (sr->GetCount() == 0)
			{
				deleteId.push_back(resources[i]->GetResourceId());
				printf("ResourceId to delete: %d\n", resources[i]->GetResourceId());
			}
		}
	}

	int numToDelete = (int)deleteId.size();
	for (int k = 0; k < numToDelete; k++)
	{
		for (int i = 0; i < (int)resources.size(); i++)
		{
			if (resources[i]->GetResourceId() == deleteId.back())
			{
				printf("GC deleting: resId=%d\n", resources[i]->GetResourceId());
				resources.erase(resources.begin() + i);
				deleteId.pop_back();
				break;
			}
		}
	}
}

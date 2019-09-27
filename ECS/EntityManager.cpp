#include "EntityManager.h"

#include "ComponentManager.h"

EntityManager::~EntityManager()
{
	//for (int i = 0; i < (int)entities.size(); i++)
	//	entities[i]->ClearComponentIds();
	entities.clear();
}

EntityId EntityManager::CreateEntity()
{
	entities.push_back(new Entity());
	return entities.back()->GetEntityId();
}

void EntityManager::DeleteEntity(EntityId id)
{
	for (int i = 0; i < (int)entities.size(); i++)
	{
		if (entities[i]->GetEntityId() == id)
		{
			//for (int k = 0; k < (int)pointerBag->GetComponentManager()->)

			std::vector<ComponentId> compIds = entities[i]->GetComponentIds();
			for (int k = 0; k < (int)compIds.size(); k++)
			{
				pointerBag->GetComponentManager()->DeleteComponent(compIds[k]);
			}

			// TODO: also delete components associated with this entity
			entities.erase(entities.begin() + i);
			break;
		}
	}		
}

Entity* EntityManager::GetEntity(EntityId id)
{
	for (int i = 0; i < (int)entities.size(); i++)
		if (entities[i]->GetEntityId() == id)
			return entities[i];

	return nullptr; // did not find entity with that id
}

void EntityManager::RemoveEmptyEntities()
{
	std::vector<EntityId> toDeleteId;

	for (int i = 0; i < (int)entities.size(); i++)
	{
		if (entities[i]->GetComponentIds().empty())
			toDeleteId.push_back(entities[i]->GetEntityId());
	}

	for (int i = 0; i < (int)toDeleteId.size(); i++)
		DeleteEntity(toDeleteId[i]);

	toDeleteId.clear();
}


/*
ComponentId EntityManager::FindComponentIdByEntitysComponentIds(EntityId id, ComponentTypeId typeId)
{
	std::vector<ComponentId> compIds = GetEntity(id)->GetComponentIds();
	for (int i = 0; i < (int)compIds.size(); i++)
		if (pointerBag->GetComponentManager()->GetComponent(compIds[i])->GetComponentTypeId() == typeId)
			return compIds[i];

	return 0; // did not find any
}

*/
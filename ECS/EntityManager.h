#pragma once

#include <vector>
#include "Entity.h"
#include "../PointerBag.h"
#include "Component.h"

class EntityManager
{
public:
	EntityManager(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	~EntityManager();

	EntityId CreateEntity();
	void DeleteEntity(EntityId id);
	Entity* GetEntity(EntityId id);

	//ComponentId FindComponentIdByEntitysComponentIds(EntityId id, ComponentTypeId typeId);

	void RemoveEmptyEntities();

private:
	PointerBag* pointerBag = nullptr;
	std::vector<Entity*> entities;
};

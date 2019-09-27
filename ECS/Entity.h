#pragma once

#include <vector>
#include "Component.h"

using EntityId = int;

class Entity
{
	//static EntityId serial;
protected:
	static EntityId serial;
	EntityId id;

public:
	Entity() : id(++serial) { }
	virtual ~Entity() { }

	EntityId GetEntityId() { return id; }
	
	// Component reverse lookup table
	void AddComponentIds(ComponentId id) { componentsIds.push_back(id); }
	void RemoveComponentIds(ComponentId id)
	{
		for (int i = 0; i < (int)componentsIds.size(); i++)
		{
			if (componentsIds[i] == id)
			{
				componentsIds.erase(componentsIds.begin() + i);
				break;
			}
		}
	}
	//void ClearComponentIds() { componentsIds.clear(); }
	std::vector<ComponentId> GetComponentIds() { return componentsIds; }

private:
	//EntityId id;
	std::vector<ComponentId> componentsIds;
};

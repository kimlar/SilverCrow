#pragma once

#include <vector>
#include "Component.h"
#include "Entity.h"
#include "../PointerBag.h"

class ComponentManager
{
public:
	ComponentManager(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	~ComponentManager() {}

	ComponentId CreateComponent(EntityId entityId, Component* component);
	void DeleteComponent(ComponentId id);
	Component* GetComponent(ComponentId id);
	Component* GetComponentByIndex(int index) { return components[index]; }
	int GetComponentsSize() { return (int)components.size(); }

private:
	PointerBag* pointerBag = nullptr;
	std::vector<Component*> components;
};

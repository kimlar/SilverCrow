#include "ComponentManager.h"

#include "EntityManager.h"

ComponentId ComponentManager::CreateComponent(EntityId entityId, Component* component)
{
	component->SetOwnerId(entityId);
	components.push_back(component);
	ComponentId componentId = components.back()->GetComponentId();
	pointerBag->GetEntityManager()->GetEntity(entityId)->AddComponentIds(componentId);
	return componentId;
}

void ComponentManager::DeleteComponent(ComponentId id)
{
	for (int i = 0; i < (int)components.size(); i++)
	{
		if (components[i]->GetComponentId() == id)
		{
			pointerBag->GetEntityManager()->GetEntity(components[i]->GetOwnerId())->RemoveComponentIds(id);
			components.erase(components.begin() + i);
			break;
		}
	}
}

Component* ComponentManager::GetComponent(ComponentId id)
{
	for (int i = 0; i < (int)components.size(); i++)
		if (components[i]->GetComponentId() == id)
			return components[i];

	return nullptr; // did not find component by that id
}

#pragma once

#include <SDL.h>
//#include "Components/TransformComponent.h"
//#include "Components/SpriteComponent.h"

//class TransformComponent;

//#include "Entity.h"
//class Entity;

using EntityId = int;

using ComponentId = int;
using ComponentTypeId = int;

class Component
{
	static ComponentId serial;

public:
	enum class ComponentType
	{
		Transform = 0,
		Velocity,
		Sprite,
		Input,
		Count // Number of systems
	};
	
	Component() : id(++serial) {}
	virtual ~Component() {}

	ComponentId GetComponentId() { return id; }
	ComponentTypeId GetComponentTypeId() { return typeId; }

	// Returns
	//TransformComponent* GetTransformComponent() { return static_cast<TransformComponent*>(this); }
	//TransformComponent* GetTransformComponent() { return (TransformComponent*)this; }

	void SetOwnerId(EntityId ownerId) { this->ownerId = ownerId; }
	EntityId GetOwnerId() { return ownerId; }

private:
	ComponentId id;

protected:
	ComponentTypeId typeId;
	EntityId ownerId;
};

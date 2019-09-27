#pragma once

#include "ECS/Entity.h"
#include "PointerBag.h"

#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "Sprite.h"

//#include "GameObject.h"

#include "Resource.h"
#include "SpriteResource.h"

class MoonM148 : public Entity
{
public:
	MoonM148(PointerBag* pointerBag) : pointerBag(pointerBag) { Create(); }
	virtual ~MoonM148() { Destroy(); }

	void Create();
	void Destroy();

	//TransformComponent* GetTransformComponent() { return static_cast<TransformComponent*>(componentManager->GetComponent(transformId)); }
	//SpriteComponent* GetSpriteComponent() { return static_cast<SpriteComponent*>(componentManager->GetComponent(spriteId)); }

	void SetPosition(float x, float y)
	{
		TransformComponent* transformComponent = static_cast<TransformComponent*>(componentManager->GetComponent(transformId));
		transformComponent->position = Vector2(x, y);
	}

private:
	PointerBag* pointerBag;

	// General
	Sprite* moonSprite = nullptr;;

	// ECS managers
	EntityManager* entityManager = nullptr;
	ComponentManager* componentManager = nullptr;

	// ECS data
	EntityId entityId;
	ComponentId transformId;
	ComponentId spriteId;

	// Resource
	ResourceManager* resourceManager = nullptr;
	ResourceId spriteResourceId;
};

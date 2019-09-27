#pragma once

#include "ECS/Entity.h"
#include "PointerBag.h"

#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/InputComponent.h"
#include "ECS/Components//VelocityComponent.h"
#include "Sprite.h"

//#include "GameObject.h"

#include "Resource.h"
#include "SpriteResource.h"


class FighterF50 : public Entity
{
public:
	FighterF50(PointerBag* pointerBag) : pointerBag(pointerBag) { Create(); }
	virtual ~FighterF50() { Destroy(); }

	void Create();
	void Destroy();

	/*
	void SetPosition(float x, float y)
	{
		TransformComponent* transformComponent = static_cast<TransformComponent*>(componentManager->GetComponent(transformId));
		transformComponent->position = Vector2(x, y);
	}
	*/

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
	ComponentId inputId;
	ComponentId velocityId;

	// Resource
	ResourceManager* resourceManager = nullptr;
	ResourceId spriteResourceId;
};

#include "FighterF50.h"

#include "ResourceManager.h"

void FighterF50::Create()
{
	// Resource
	resourceManager = pointerBag->GetResourceManager();
	spriteResourceId = resourceManager->AddResource(Resource::ResourceType::Sprite, "enemy-gray-L74.png");
	Resource* resource = resourceManager->GetResource(spriteResourceId);
	SpriteResource* spriteResource = static_cast<SpriteResource*>(resource);
	moonSprite = spriteResource->GetSprite();


	// General
	//moonSprite = new Sprite(pointerBag->GetRenderer());
	//moonSprite->Load("moon-M147.png");

	// ECS managers
	entityManager = pointerBag->GetEntityManager();
	componentManager = pointerBag->GetComponentManager();

	// ECS data
	entityId = entityManager->CreateEntity();
	transformId = componentManager->CreateComponent(entityId, new TransformComponent(Vector2(400.0f, 600.0f)));
	spriteId = componentManager->CreateComponent(entityId, new SpriteComponent(moonSprite, transformId));
	inputId = componentManager->CreateComponent(entityId, new InputComponent());
	velocityId = componentManager->CreateComponent(entityId, new VelocityComponent());
}

void FighterF50::Destroy()
{
	pointerBag->GetResourceManager()->RemoveResource(spriteResourceId);

	moonSprite = nullptr;

	entityManager->DeleteEntity(entityId);
}



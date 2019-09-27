#include "MoonM147.h"

#include "ResourceManager.h"

void MoonM147::Create()
{
	// Resource
	resourceManager = pointerBag->GetResourceManager();
	spriteResourceId = resourceManager->AddResource(Resource::ResourceType::Sprite, "moon-M147.png");
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
}

void MoonM147::Destroy()
{
	pointerBag->GetResourceManager()->RemoveResource(spriteResourceId);

	//moonSprite->Unload();
	//delete moonSprite;
	moonSprite = nullptr;

	TransformComponent* transform_ = static_cast<TransformComponent*>(componentManager->GetComponent(transformId));
	delete transform_;
	transform_ = nullptr;

	SpriteComponent* sprite_ = static_cast<SpriteComponent*>(componentManager->GetComponent(spriteId));
	delete sprite_;
	sprite_ = nullptr;
}

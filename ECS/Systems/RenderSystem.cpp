#include "RenderSystem.h"

#include "../ComponentManager.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"


RenderSystem::RenderSystem(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	typeId = _typeId;
}

void RenderSystem::Initialize()
{
	renderer = &pointerBag->GetWindow()->GetRenderer();
}

void RenderSystem::Render()
{
	for (int i = 0; i < (int)pointerBag->GetComponentManager()->GetComponentsSize(); i++)
	{
		if (pointerBag->GetComponentManager()->GetComponentByIndex(i)->GetComponentTypeId() == (ComponentTypeId)Component::ComponentType::Sprite)
		{
			Component* component = pointerBag->GetComponentManager()->GetComponentByIndex(i);
			SpriteComponent* spriteComponent = static_cast<SpriteComponent*>(component);

			// Update sprite position
			Component* component2 = pointerBag->GetComponentManager()->GetComponent(spriteComponent->transformComponentId);
			TransformComponent* transformComponent = static_cast<TransformComponent*>(component2);
			spriteComponent->sprite->SetPosition((int)transformComponent->position.x, (int)transformComponent->position.y);
			
			SDL_RenderCopy(&pointerBag->GetWindow()->GetRenderer(), &spriteComponent->sprite->GetTexture(), &spriteComponent->sprite->GetSrcRect(), &spriteComponent->sprite->GetDstRect());
		}
	}
}

void RenderSystem::Terminate()
{
	renderer = nullptr;
}

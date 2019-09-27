#include "PlayerControlSystem.h"

#include "../ComponentManager.h"
#include "../Components/InputComponent.h"

PlayerControlSystem::PlayerControlSystem(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	typeId = _typeId;
}

void PlayerControlSystem::HandleEvent(SDL_Event& e)
{
	// ...
}

void PlayerControlSystem::Update(float dt)
{
	// Move(dt)
	
	// Update position

	// Update sprite (animation)

	// Update animation

	// Update bullets (THIS SHOULD BE AN OWN GAME OBJECT... MOVE IT OUT)!!!!
}

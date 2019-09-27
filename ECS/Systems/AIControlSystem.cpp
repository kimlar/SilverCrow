#include "AIControlSystem.h"

#include "../ComponentManager.h"
#include "../Components/InputComponent.h"


AIControlSystem::AIControlSystem(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	typeId = _typeId;
}

void AIControlSystem::Update(float dt)
{
	// Update AI (dt)
	// IN: Input, Position
	// OUT: Input

	// Move (dt)
	// IN: Position, Velocity
	// OUT: Position

	// Update position
	// IN: Position
	// OUT: Position

	// Update animation (dt)
	// IN: Animation
	// OUT: Animation

	// ... Update bullets (dt) <------- THIS SHOULD BE AN OWN GAME OBJECT
}

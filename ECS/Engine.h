#pragma once

#include <SDL.h>
#include "../PointerBag.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "../Texture.h"

#include "../Timer.h"

class ECS_Engine
{
public:
	ECS_Engine(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	~ECS_Engine() {}

	void Initialize();
	void HandleEvent(SDL_Event& event);
	void Update(float dt);
	void Render();
	void Terminate();

private:
	PointerBag* pointerBag = nullptr;

	// ECS managers
	EntityManager* entityManager = nullptr;
	ComponentManager* componentManager = nullptr;
	SystemManager* systemManager = nullptr;

	// ECS data
	SystemId renderSystemId;

	// Timing
	Timer engineTimer;
	double et;
	int etFrames;
};

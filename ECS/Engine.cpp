#include "../ECS/Engine.h"

#include <vector>
#include "../ECS/Component.h"
#include "../ECS/Components/TransformComponent.h"
#include "../PointerBag.h"
#include "../Window.h"

#include "../ECS/Systems/RenderSystem.h"
#include "../ECS/Entity.h"

void ECS_Engine::Initialize()
{
	// Create ECS managers
	entityManager = new EntityManager(pointerBag);
	componentManager = new ComponentManager(pointerBag);
	systemManager = new SystemManager(pointerBag);
	pointerBag->SetECS(entityManager, componentManager, systemManager);

	// Create render system
	renderSystemId = systemManager->CreateSystem(new RenderSystem(pointerBag));

	// Init timer
	engineTimer.Start();
	et = 0.0;
	etFrames = 0;
}

void ECS_Engine::HandleEvent(SDL_Event& event)
{
}

void ECS_Engine::Update(float dt)
{
	engineTimer.Stop();
	//double dur = engineTimer.GetDuration();
	//if (et >= 0.02)
	engineTimer.Print();
	et += engineTimer.GetDuration();
	++etFrames;
	if (et >= 1.0)
	{
		et = 0.0;
		printf("Frames: %d\n", etFrames);
		etFrames = 0;
	}

	engineTimer.Start();
}

void ECS_Engine::Render()
{
	systemManager->GetSystem(renderSystemId)->Render();
}

void ECS_Engine::Terminate()
{
	systemManager->DestroySystem(renderSystemId);

	delete entityManager;
	entityManager = nullptr;

	delete componentManager;
	componentManager = nullptr;

	delete systemManager;
	systemManager = nullptr;
}

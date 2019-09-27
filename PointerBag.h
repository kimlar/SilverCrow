#pragma once

#include <SDL.h>

class AppFSM;
class Window;

class EntityManager;
class ComponentManager;
class SystemManager;

class ResourceManager;

class PointerBag
{
public:
	PointerBag() { run = true; }
	~PointerBag() {}

	void SetAppFSM(AppFSM* appFSM) { this->appFSM = appFSM; }
	AppFSM* GetAppFSM() { return appFSM; }

	void SetWindow(Window* window) { this->window = window; }
	Window* GetWindow() { return window; }

	void SetRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }
	SDL_Renderer& GetRenderer() { return *renderer; }

	// ECS
	void SetECS(EntityManager* entityManager, ComponentManager* componentManager, SystemManager* systemManager)
	{
		this->entityManager = entityManager;
		this->componentManager = componentManager;
		this->systemManager = systemManager;
	}
	EntityManager* GetEntityManager() { return entityManager; }
	ComponentManager* GetComponentManager() { return componentManager; }
	SystemManager* GetSystemManager() { return systemManager; }

	// Resource
	void SetResourceManager(ResourceManager* resourceManager) { this->resourceManager = resourceManager; }
	ResourceManager* GetResourceManager() { return resourceManager; }

	bool run;
private:
	AppFSM* appFSM = nullptr;
	Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// ECS
	EntityManager* entityManager = nullptr;
	ComponentManager* componentManager = nullptr;
	SystemManager* systemManager = nullptr;

	// Resource
	ResourceManager* resourceManager = nullptr;
};

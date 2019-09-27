#pragma once

#include <vector>
#include "System.h"
#include "../PointerBag.h"
#include "Systems/RenderSystem.h"

class SystemManager
{
public:
	SystemManager(PointerBag* pointerBag);
	~SystemManager();

	SystemId CreateSystem(System* system);
	void DestroySystem(SystemId id);
	System* GetSystem(SystemId id);

private:
	PointerBag* pointerBag = nullptr;
	std::vector<System*> systems;
};

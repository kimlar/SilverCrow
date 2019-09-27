#include "SystemManager.h"

SystemManager::SystemManager(PointerBag* pointerBag) : pointerBag(pointerBag)
{
}

SystemManager::~SystemManager()
{
	//systems.clear();
}

SystemId SystemManager::CreateSystem(System* system)
{
	systems.push_back(system);
	systems.back()->Initialize();
	return systems.back()->GetSystemId();
}

void SystemManager::DestroySystem(SystemId id)
{
	for (int i = 0; i < (int)systems.size(); i++)
	{
		if (systems[i]->GetSystemId() == id)
		{
			systems[i]->Terminate();
			systems.erase(systems.begin() + i);
			break;
		}
	}
}

System* SystemManager::GetSystem(SystemId id)
{
	for (int i = 0; i < (int)systems.size(); i++)
		if (systems[i]->GetSystemId() == id)
			return systems[i];

	return nullptr; // did not find system with that id
}

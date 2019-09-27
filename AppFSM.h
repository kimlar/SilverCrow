#pragma once

#include <string>
#include <vector>
#include "PointerBag.h"
#include "AppState.h"

class AppFSM
{
public:
	AppFSM(PointerBag* pointerBag);
	~AppFSM();

	void Create();
	void Destroy();

	void UpdateFSM();

	//
	void SetActiveState(std::string stateName);

	// State
	void Update();
	void Render();

private:
	PointerBag* pointerBag = nullptr;
	std::vector<AppState*> appStates;
	int activeState;
	int gotoState;
};

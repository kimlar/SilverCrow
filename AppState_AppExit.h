#pragma once

#include "AppState.h"
#include "PointerBag.h"

class AppState_AppExit : public AppState
{
public:
	AppState_AppExit(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "AppExit"; }
	~AppState_AppExit() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag* pointerBag = nullptr;
};

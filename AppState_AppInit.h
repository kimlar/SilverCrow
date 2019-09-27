#pragma once

#include "AppState.h"
#include "PointerBag.h"

class AppState_AppInit : public AppState
{
public:
	AppState_AppInit(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "AppInit"; }
	~AppState_AppInit() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag* pointerBag = nullptr;
	bool windowReady;
};

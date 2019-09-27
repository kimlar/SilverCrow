#pragma once

#include "AppState.h"
#include "PointerBag.h"

class AppState_Options : public AppState
{
public:
	AppState_Options(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "Options"; }
	~AppState_Options() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag * pointerBag = nullptr;
};

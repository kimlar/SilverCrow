#pragma once

#include "AppState.h"
#include "PointerBag.h"

class AppState_Start : public AppState
{
public:
	AppState_Start(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "Start"; }
	~AppState_Start() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag* pointerBag = nullptr;
};

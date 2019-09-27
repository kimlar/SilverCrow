#pragma once

#include "AppState.h"
#include "PointerBag.h"
#include "Game.h"

class AppState_PlayGame : public AppState
{
public:
	AppState_PlayGame(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "PlayGame"; }
	~AppState_PlayGame() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag* pointerBag = nullptr;
	bool pause;

	Game* game = nullptr;
};

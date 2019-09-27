#pragma once

#include "AppState.h"
#include "PointerBag.h"
#include "Texture.h"

class AppState_LoadGame : public AppState
{
public:
	AppState_LoadGame(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "LoadGame"; }
	~AppState_LoadGame() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag * pointerBag = nullptr;

	Texture* texture;
	SDL_Rect textureRect;
};

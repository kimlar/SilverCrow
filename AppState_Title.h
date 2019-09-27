#pragma once

#include "AppState.h"
#include "PointerBag.h"
#include "Texture.h"

class AppState_Title : public AppState
{
public:
	AppState_Title(PointerBag* pointerBag) : pointerBag(pointerBag) { stateName = "Title"; }
	~AppState_Title() {}

	void OnEnter();
	void OnExit();

	void OnUpdate();
	void OnRender();

private:
	PointerBag* pointerBag = nullptr;

	Texture* texture;
	SDL_Rect textureRect;
};

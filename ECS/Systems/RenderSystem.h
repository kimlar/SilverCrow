#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
#include "../../Window.h"
#include "../System.h"
#include "../../Texture.h"
#include <vector>
#include <string>
#include "../../Vector2.h"

class RenderSystem : public System
{
	const SystemTypeId _typeId = (SystemTypeId)SystemType::Render;

public:
	RenderSystem(PointerBag* pointerBag);
	virtual ~RenderSystem() {}

	void Initialize();
	void HandleEvent(SDL_Event& e) {}
	void Update(float dt) {}
	void Render();
	void Terminate();

private:
	PointerBag* pointerBag = nullptr;
	SDL_Renderer* renderer = nullptr;
};

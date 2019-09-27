#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
//#include "../../Window.h"
#include "../System.h"
//#include "../../Texture.h"
//#include <vector>
//#include <string>
//#include "../../Vector2.h"

class PlayerControlSystem : public System
{
	const SystemTypeId _typeId = (SystemTypeId)SystemType::PlayerControl;

public:
	PlayerControlSystem(PointerBag* pointerBag);
	virtual ~PlayerControlSystem() {}

	void Initialize() {}
	void HandleEvent(SDL_Event& e);
	void Update(float dt);
	void Render() {}
	void Terminate() {}

private:
	PointerBag * pointerBag = nullptr;
	//SDL_Renderer* renderer = nullptr;
};

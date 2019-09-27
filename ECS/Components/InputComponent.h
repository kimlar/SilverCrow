#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
#include "../Component.h"
//#include "../../Vector2.h"

class InputComponent : public Component
{
	const ComponentTypeId _typeId = (ComponentTypeId)ComponentType::Input;

public:
	InputComponent() { typeId = _typeId; }

	// All input controller actions. Think a game controller
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	bool fireWeaponA;
};

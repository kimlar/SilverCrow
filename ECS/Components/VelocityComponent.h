#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
#include "../Component.h"
#include "../../Vector2.h"

class VelocityComponent : public Component
{
	const ComponentTypeId _typeId = (ComponentTypeId)ComponentType::Velocity;

public:
	VelocityComponent(Vector2 velocity = Vector2(0.0f, 0.0f)) : velocity(velocity) { typeId = _typeId; }

	Vector2 velocity;
};

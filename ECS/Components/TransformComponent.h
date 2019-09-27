#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
#include "../Component.h"
#include "../../Vector2.h"

class TransformComponent : public Component
{
	const ComponentTypeId _typeId = (ComponentTypeId)ComponentType::Transform;

public:
	TransformComponent(Vector2 position, float rotation = 0.0f, float scale = 0.0f) : position(position), rotation(rotation), scale(scale) { typeId = _typeId; }

	Vector2 position;
	float rotation;
	float scale;		
};

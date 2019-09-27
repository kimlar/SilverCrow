#pragma once

#include <SDL.h>
#include "../../PointerBag.h"
#include "../../Window.h"
#include "../Component.h"
#include "../../Sprite.h"

class SpriteComponent : public Component
{
	const ComponentTypeId _typeId = (ComponentTypeId)ComponentType::Sprite;

public:
	SpriteComponent(Sprite* sprite, ComponentId transformId) : sprite(sprite), transformComponentId(transformId) { typeId = _typeId; }

	Sprite* sprite = nullptr;
	ComponentId transformComponentId;
};

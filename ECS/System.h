#pragma once

#include <SDL.h>

using SystemId = int;
using SystemTypeId = int;

class System
{
	static SystemId serial;

public:
	enum class SystemType
	{
		Input = 0,
		Physics,
		Render,
		PlayerControl,
		AIControl,
		Count // Number of systems
	};

	System() : id(++serial) {}
	virtual ~System() {}

	virtual void Initialize() = 0;
	virtual void HandleEvent(SDL_Event& e) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Terminate() = 0;

	SystemId GetSystemId() { return id; }
	SystemTypeId GetSystemTypeId() { return typeId; }

private:
	SystemId id;

protected:
	SystemTypeId typeId;
};

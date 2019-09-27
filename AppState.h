#pragma once

#include <string>
#include "PointerBag.h"

class AppState
{
public:
	AppState() {}
	~AppState() {}

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

	std::string GetStateName() { return stateName; }
protected:
	std::string stateName;
private:
};

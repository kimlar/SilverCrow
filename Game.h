#pragma once

#include <SDL.h>
#include <vector>
#include "PointerBag.h"
#include "ECS/Engine.h"

///////////////////////////////////
#include "Player.h"
#include "Enemy.h"
///////////////////////////////////

//#include "GameObject.h"

#include "MoonM147.h"
#include "MoonM148.h"

#include "FighterF50.h"


class Game
{
public:
	Game(PointerBag* pointerBag);
	~Game();

	void Create();
	void Destroy();
	void HandleEvent(SDL_Event& e);
	void Update(float dt);
	void Render();
	
	//void* Burn() { return gameObjects.back()->GetType(); }

private:
	PointerBag* pointerBag = nullptr;
	ECS_Engine* ecsEngine = nullptr;
	
	///////////////////////////////////
	Player* player;
	Enemy* enemy;
	///////////////////////////////////

	//MoonM147* moonM147;
	//MoonM148* moonM148;

	//std::vector<MoonM147*> moons;
	//std::vector<Entity*> moons;
	//std::vector<GameObject*> gameObjects;	
	std::vector<Entity*> gameObjects;
};

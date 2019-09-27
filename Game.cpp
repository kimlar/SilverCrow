#include "Game.h"

///////////////////////////////////
#include "Window.h"
///////////////////////////////////

#include "UtilRandom.h"
#include "ResourceManager.h"
//#include "ECS/Components/TransformComponent.h"

Game::Game(PointerBag* pointerBag) : pointerBag(pointerBag)
{

}

Game::~Game()
{

}

void Game::Create()
{
	gameObjects.clear();

	ecsEngine = new ECS_Engine(pointerBag);
	ecsEngine->Initialize();

	///////////////////////////////////
	player = new Player(pointerBag->GetRenderer());
	player->Create("player-ship.txt", "player-ship.png", pointerBag->GetWindow()->GetWidth() / 2 - 105 / 2, pointerBag->GetWindow()->GetHeight() / 2 - 81 / 2);
	player->GetAnimation().GotoFrame(1);
	
	enemy = new Enemy(pointerBag->GetRenderer());
	enemy->Create("enemy-gray-L74.txt", "enemy-gray-L74.png", 100, 100);
	enemy->GetAnimation().GotoFrame(0);
	///////////////////////////////////

	
	//moonM147 = new MoonM147(pointerBag);
	//moonM147->Create();

	//moonM148 = new MoonM148(pointerBag);
	//moonM148->Create();



	/*
	for (int i = 0; i < 32; i++)
	{
		if (rand() % 2 == 0)
		{
			gameObjects.push_back(new MoonM147(pointerBag));
			MoonM147* tempObj = static_cast<MoonM147*>(gameObjects.back());
			tempObj->SetPosition((float)(rand() % 2560), (float)(rand() % 1440));
		}
		else
		{
			gameObjects.push_back(new MoonM148(pointerBag));
			MoonM148* tempObj = static_cast<MoonM148*>(gameObjects.back());
			tempObj->SetPosition((float)(rand() % 2560), (float)(rand() % 1440));
		}

	}
	*/

	gameObjects.push_back(new FighterF50(pointerBag));
}

void Game::Destroy()
{

	///////////////////////////////////
	player->Destroy();
	delete player;
	player = nullptr;

	enemy->Destroy();
	delete enemy;
	enemy = nullptr;
	///////////////////////////////////

	for (auto& i : gameObjects)
	{
		delete i;
	}

	//moonM147->Destroy();
	//delete moonM147;
	//moonM147 = nullptr;

	//moonM148->Destroy();
	//delete moonM148;
	//moonM148 = nullptr;
	
	ecsEngine->Terminate();
	delete ecsEngine;
	ecsEngine = nullptr;
	
	
	// GC action
	pointerBag->GetResourceManager()->DoGarbageCollection();
}

void Game::HandleEvent(SDL_Event& e)
{
	ecsEngine->HandleEvent(e);

	///////////////////////////////////
	player->HandleEvent(e);
	///////////////////////////////////
}

void Game::Update(float dt)
{
	//pointerBag->GetResourceManager()->DoGarbageCollection();

	ecsEngine->Update(dt);

	///////////////////////////////////
	player->Update(dt);
	enemy->Update(dt);
	///////////////////////////////////
}

void Game::Render()
{
	ecsEngine->Render();

	///////////////////////////////////
	player->Render();
	enemy->Render();
	///////////////////////////////////
}

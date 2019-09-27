#include "AppState_LoadGame.h"

#include "AppFSM.h"
#include "Window.h"

void AppState_LoadGame::OnEnter()
{
	texture = new Texture(pointerBag->GetWindow()->GetRenderer());
	texture->Load("Loading.png");
	textureRect = { 0, 0, texture->GetWidth(), texture->GetHeight() };
}

void AppState_LoadGame::OnExit()
{
	texture->Unload();
	delete texture;
	texture = nullptr;
}

void AppState_LoadGame::OnUpdate()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		pointerBag->GetWindow()->HandleEvent(e);
	}

	bool doneLoading = false;
	doneLoading = true;
	if(doneLoading)
		pointerBag->GetAppFSM()->SetActiveState("PlayGame");
}

void AppState_LoadGame::OnRender()
{
	pointerBag->GetWindow()->ClearScreen();
	SDL_RenderCopy(&pointerBag->GetWindow()->GetRenderer(), &texture->GetTexture(), NULL, NULL);
	pointerBag->GetWindow()->UpdateScreen();
}

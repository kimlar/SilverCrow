#include "AppState_Title.h"

#include "AppFSM.h"
#include "Window.h"
#include "ResourceManager.h"

void AppState_Title::OnEnter()
{
	//ResourceManager* resourceManager = new ResourceManager(pointerBag);

	texture = new Texture(pointerBag->GetWindow()->GetRenderer());
	texture->Load("Title.png");
	textureRect = { 0, 0, texture->GetWidth(), texture->GetHeight() };
}

void AppState_Title::OnExit()
{
	texture->Unload();
	delete texture;
	texture = nullptr;
}

void AppState_Title::OnUpdate()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		pointerBag->GetWindow()->HandleEvent(e);

		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_p:
				pointerBag->GetAppFSM()->SetActiveState("LoadGame");
				break;
			case SDLK_o:
				pointerBag->GetAppFSM()->SetActiveState("Options");
				break;
			case SDLK_q:
				pointerBag->GetAppFSM()->SetActiveState("AppExit");
				break;
			}
		}
	}
}

void AppState_Title::OnRender()
{
	pointerBag->GetWindow()->ClearScreen();
	SDL_RenderCopy(&pointerBag->GetWindow()->GetRenderer(), &texture->GetTexture(), NULL, NULL);
	pointerBag->GetWindow()->UpdateScreen();
}

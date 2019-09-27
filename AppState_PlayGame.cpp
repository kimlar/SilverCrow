#include "AppState_PlayGame.h"

#include "AppFSM.h"
#include "Window.h"

void AppState_PlayGame::OnEnter()
{
	pause = false;

	game = new Game(pointerBag);
	game->Create();
}

void AppState_PlayGame::OnExit()
{
	game->Destroy();
	delete game;
	game = nullptr;
}

void AppState_PlayGame::OnUpdate()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		pointerBag->GetWindow()->HandleEvent(e);

		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_t:
				pointerBag->GetAppFSM()->SetActiveState("Title");
				break;
			case SDLK_p:
				pause = !pause;
				break;
			}
		}

		game->HandleEvent(e);
	}

	// Pause game (skip game logic)
	if (pause)
		return;

	// Logic
	float dt = pointerBag->GetWindow()->GetDT();
	game->Update(dt);
}

void AppState_PlayGame::OnRender()
{
	// Render
	pointerBag->GetWindow()->ClearScreen();
	game->Render();
	pointerBag->GetWindow()->UpdateScreen();
}

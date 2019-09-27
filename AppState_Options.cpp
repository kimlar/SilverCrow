#include "AppState_Options.h"

#include "AppFSM.h"
#include "Window.h"

void AppState_Options::OnEnter()
{

}

void AppState_Options::OnExit()
{

}

void AppState_Options::OnUpdate()
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
			case SDLK_v:
				//
				break;
			case SDLK_s:
				//
				break;
			}
		}

	}
}

void AppState_Options::OnRender()
{
	pointerBag->GetWindow()->ClearScreen();
	pointerBag->GetWindow()->UpdateScreen();
}

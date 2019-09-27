#include "AppState_AppExit.h"

#include "ResourceManager.h"
#include "Window.h"

void AppState_AppExit::OnEnter()
{
	pointerBag->run = false; // Shutdown app loop
}

void AppState_AppExit::OnExit()
{
	pointerBag->GetResourceManager()->Destroy();
	pointerBag->GetWindow()->Destroy();
}

void AppState_AppExit::OnUpdate()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		pointerBag->GetWindow()->HandleEvent(e);
	}
}

void AppState_AppExit::OnRender()
{
	pointerBag->GetWindow()->ClearScreen();
	pointerBag->GetWindow()->UpdateScreen();
}

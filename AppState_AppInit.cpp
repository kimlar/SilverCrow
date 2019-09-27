#include "AppState_AppInit.h"

#include "AppFSM.h"
#include "Window.h"
#include "UtilRandom.h"
#include "ResourceManager.h"

void AppState_AppInit::OnEnter()
{
	// Set random seed
	SetRandomSeed();

	// Create the window
	Window* window = new Window(pointerBag);
	window->Create();

	// Create the resource manager
	ResourceManager* resourceManager = new ResourceManager(pointerBag);
}

void AppState_AppInit::OnExit()
{

}

void AppState_AppInit::OnUpdate()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		pointerBag->GetWindow()->HandleEvent(e);
	}

	// Ugly hack to ensure that window has gotten set up. Need to run through twice
	if(windowReady)
		pointerBag->GetAppFSM()->SetActiveState("Title");
	windowReady = true;
}

void AppState_AppInit::OnRender()
{
	pointerBag->GetWindow()->ClearScreen();
	pointerBag->GetWindow()->UpdateScreen();
}

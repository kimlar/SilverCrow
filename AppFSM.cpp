#include "AppFSM.h"

#include "Window.h"

#include "AppState_Start.h"
#include "AppState_AppInit.h"
#include "AppState_AppExit.h"
#include "AppState_Title.h"
#include "AppState_LoadGame.h"
#include "AppState_PlayGame.h"
#include "AppState_Options.h"

AppFSM::AppFSM(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	pointerBag->SetAppFSM(this);

	activeState = 0;
	gotoState = 0;
}

AppFSM::~AppFSM()
{

}

void AppFSM::Create()
{
	appStates.push_back(new AppState_Start(pointerBag));
	appStates.push_back(new AppState_AppInit(pointerBag));
	appStates.push_back(new AppState_AppExit(pointerBag));
	appStates.push_back(new AppState_Title(pointerBag));
	appStates.push_back(new AppState_LoadGame(pointerBag));
	appStates.push_back(new AppState_PlayGame(pointerBag));
	appStates.push_back(new AppState_Options(pointerBag));

	// Inject first state into the FSM
	SetActiveState("Start");
	appStates[gotoState]->OnEnter();
	activeState = gotoState;
}

void AppFSM::Destroy()
{
	// Inject last state into the FSM
	SetActiveState("AppExit");
	appStates[gotoState]->OnExit();
	activeState = gotoState;


	appStates.clear();

	activeState = 0;
	gotoState = 0;
}

void AppFSM::UpdateFSM()
{
	// Change state?
	if (activeState != gotoState)
	{
		appStates[activeState]->OnExit();
		appStates[gotoState]->OnEnter();
		activeState = gotoState;
	}

	// Process current state
	Update();
	if (!pointerBag->GetWindow()->isMinimized())
		Render();
	else
		SDL_Delay(1); // Ugly hack to not burn CPU cycles while minimized
}

void AppFSM::SetActiveState(std::string stateName)
{
	for (int i = 0; i < (int)appStates.size(); i++)
	{
		if (appStates[i]->GetStateName() == stateName)
		{
			gotoState = i;
			break;
		}
	}
}

void AppFSM::Update()
{
	appStates[activeState]->OnUpdate();
}

void AppFSM::Render()
{
	appStates[activeState]->OnRender();
}

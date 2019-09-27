#include "AppState_Start.h"

#include "PointerBag.h"
#include "AppFSM.h"

void AppState_Start::OnEnter()
{
	pointerBag->GetAppFSM()->SetActiveState("AppInit");
	pointerBag->GetAppFSM()->UpdateFSM();
}

void AppState_Start::OnExit()
{

}

void AppState_Start::OnUpdate()
{

}

void AppState_Start::OnRender()
{

}

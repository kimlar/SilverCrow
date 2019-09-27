#include <SDL.h>
#include "PointerBag.h"
#include "AppFSM.h"

int main(int argc, char* argv[])
{
	PointerBag* pointerBag = new PointerBag();

	AppFSM* appFSM = new AppFSM(pointerBag);
	appFSM->Create();
	
	while (pointerBag->run)
		appFSM->UpdateFSM();

	appFSM->Destroy();
	delete appFSM;
	appFSM = nullptr;

	delete pointerBag;
	pointerBag = nullptr;

	return 0;
}

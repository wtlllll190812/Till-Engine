#include "Application.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	//_CrtSetBreakAlloc(9333);
	Application::instance().AppRun();
	_CrtDumpMemoryLeaks();
	return 0;
}
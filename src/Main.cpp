#include "Application.h"
#include "Input.h"

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new MYDEBUG_NEW
#else
#define MYDEBUG_NEW
#endif

#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	//临时
	Application::instance().Run();
	// 场景初始化

	/*GameLoop loop(60);
	loop.SetUpdateCallback([]()
		{
			Application::instance().Run();
			
		});
	loop.StartLoop();*/
	int* i = new int(10);
	_CrtDumpMemoryLeaks();
	return 0;
}

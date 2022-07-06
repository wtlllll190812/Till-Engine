#include "Application.h"
#include "Input.h"
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
	return 0;
}

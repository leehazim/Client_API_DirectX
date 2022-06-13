#include "CAPIEngine.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	CAPIEngine Main;
	Main.Create(hInstance, nCmdShow);
	MSG msg = Main.Run();
	return (int)msg.wParam;
}
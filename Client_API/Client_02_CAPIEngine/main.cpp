#include "CAPIEngine.h"

class LSHEngine 
	: public CAPIEngine {
public:
	LSHEngine() {

	}
	virtual ~LSHEngine() {

	}

};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();
	return (int)msg.wParam;
}
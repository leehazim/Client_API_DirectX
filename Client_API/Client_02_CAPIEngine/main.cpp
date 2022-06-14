#include "CAPIEngine.h"

class LSHEngine 
	: public CAPIEngine {
public:
	LSHEngine() {

	}
	virtual ~LSHEngine() {

	}

public:
	virtual void OnCreate() override {
		CAPIEngine::OnCreate();
		// TODO : 게임 초기화

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);
	}
	virtual void OnDestroy() override {
		// TODO : 게임 정리

		CAPIEngine::OnDestroy();
	}
	virtual void OnUpdate() override {
		CAPIEngine::OnUpdate();
		// TODO : 게임 갱신
	}

	// 복사 생성과 복사대입 금지를 위해 접근 제한
private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();
	
	// 엔진 클래스의 복사생성이나 대입이 일어나는 것을 막기
	/*LSHEngine tA = Game;
	LSHEngine tB;
	tB = tA;*/

	return (int)msg.wParam;
}
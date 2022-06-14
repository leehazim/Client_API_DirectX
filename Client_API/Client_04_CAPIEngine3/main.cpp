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
		// TODO : ���� �ʱ�ȭ

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);
	}
	virtual void OnDestroy() override {
		// TODO : ���� ����

		CAPIEngine::OnDestroy();
	}
	virtual void OnUpdate() override {
		CAPIEngine::OnUpdate();
		// TODO : ���� ����
	}

	// ���� ������ ������� ������ ���� ���� ����
private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();
	
	// ���� Ŭ������ ��������̳� ������ �Ͼ�� ���� ����
	/*LSHEngine tA = Game;
	LSHEngine tB;
	tB = tA;*/

	return (int)msg.wParam;
}
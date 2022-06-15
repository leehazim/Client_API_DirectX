#include "CAPIEngine.h"
#include "CUnit.h"
class LSHEngine
	: public CAPIEngine {
public:
	LSHEngine() 
		: m_Unit(nullptr) {}
	virtual ~LSHEngine() {}

public:
	virtual void OnCreate() override {
		CAPIEngine::OnCreate();
		// TODO : 게임 초기화

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);

		m_Unit = new CUnit();
	}

	virtual void OnDestroy() override {
		// TODO : 게임 정리

		if (m_Unit != nullptr) {
			delete m_Unit;
		}

		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate() override {
		CAPIEngine::OnUpdate();
		
		// input
		// 메시지 루프에서 DispatchMessage로 안보내져도 되는 건가
		if (GetAsyncKeyState('A') & 0x8000) {
			m_Unit->m_X = m_Unit->m_X - 0.01f;
			//m_Unit->m_X -= 0.01f;
		}

		if (GetAsyncKeyState('D') & 0x8000) {
			m_Unit->m_X = m_Unit->m_X + 0.01f;
			//m_Unit->m_X += 0.01f;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			OutputDebugString(L"Skill_00\n");
			MessageBox(nullptr, L"Skill_00", L"Skill_00", MB_OK);
		}
		// update


		// render
		m_Unit->Render(this);

		//test
		// 비트맵 그리기위한 호환되는 메모리DC생성, 파일로부터 비트맵 불러오기
		HDC MemDC = CreateCompatibleDC(this->m_hDC);
		HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"resources/bongbong_0.bmp",
											 IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		// 그리려는 비트맵을 메모리 DC에 채우기, 비트맵 바꿔치기 빠르게 바꿔쳐준다.
		HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		BITMAP bit;
		GetObject(hBitmap, sizeof(BITMAP), &bit);
		BitBlt(this->m_hDC, 100, 100, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);

		// 사용이끝난 GDI Object들을 해제
		SelectObject(MemDC, OldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(MemDC);
	}

private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}

public:
	CUnit* m_Unit = nullptr;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();

	return (int)msg.wParam;
}
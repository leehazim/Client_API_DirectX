#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"

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

		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
	}

	virtual void OnDestroy() override {
		// TODO : 게임 정리

		if (m_Ctexture != nullptr) {
			delete m_Ctexture;
			m_Ctexture = nullptr;
		}

		if (m_Unit != nullptr) {
			delete m_Unit;
			m_Unit = nullptr;
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
		// CTexture에 받아놓은 비트맵 정보들을 받아와서 그리기
		// 그리기 등을 담당하는 엔진(매니저)클래스를 만들어 놓고
		// 텍스처들을 담는 컨테이너용 클래스를 만들어서 관리하는 방식으로 구현하는 습관(방법론)을 이해하고 가지고 있자.
		BitBlt(this->m_hDC, 
			   m_Unit->m_X, m_Unit->m_Y,
			   m_Ctexture->m_Info.bmWidth, m_Ctexture->m_Info.bmHeight, 
			   m_Ctexture->m_hMemDC, 0, 0, SRCCOPY);

		// 06.16 수정 테스트 종료후 구현
		//test
		// 비트맵 그리기위한 호환되는 메모리DC생성, 파일로부터 비트맵 불러오기
		//HDC MemDC = CreateCompatibleDC(this->m_hDC);
		//HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, L"resources/bongbong_0.bmp",
		//									 IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		//HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		//BITMAP bit;
		//GetObject(hBitmap, sizeof(BITMAP), &bit);
		//
		//// 그리려는 비트맵을 메모리 DC에 채우기, 비트맵 바꿔치기 빠르게 바꿔쳐준다.
		//BitBlt(this->m_hDC, 100, 100, bit.bmWidth, bit.bmHeight, MemDC, 0, 0, SRCCOPY);
		//
		//// 사용이끝난 GDI Object들을 해제
		//SelectObject(MemDC, OldBitmap);
		//DeleteObject(hBitmap);
		//DeleteDC(MemDC);
	}

public:
	CUnit* m_Unit = nullptr;
	CTexture* m_Ctexture = nullptr;

private:
	LSHEngine(const LSHEngine& other) {}
	LSHEngine& operator=(const LSHEngine& other) {}
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();

	return (int)msg.wParam;
}
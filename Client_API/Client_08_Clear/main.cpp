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
		this->Clear(0.7f, 0.2f, 0.6f);

		m_Unit->Render(this);
		/* 메모리 버퍼를 함수 내에서 만들지말고 비트맵을 관리하는 클래스를 설계해서 
		비트맵 파일을 불러와서 그리는 객체하나
		백버퍼를 담당하는 객체로 따로 생성해서 HIBITMAP을 가지고 있게 설정*/

		this->DrawTexture(m_Unit->m_X, m_Unit->m_Y, m_Ctexture);
		//BitBlt(this->/*백버퍼로서 그려진 비트맵을 가진 녀석*/m_pBackBuffer->m_hMemDC,
		//	   m_Unit->m_X, m_Unit->m_Y,
		//	   m_Ctexture->m_Info.bmWidth, m_Ctexture->m_Info.bmHeight, 
		//	   /*비트맵을 가진녀석*/m_Ctexture->m_hMemDC, 0, 0, SRCCOPY);

		// 메모리 버퍼에 그리기
		this->Present();
		/*BitBlt(this->m_hDC,
			   0, 0,
			   800, 600,
			   m_pBackBuffer->m_hMemDC,
			   0, 0, SRCCOPY);*/
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
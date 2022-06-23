#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObject.h"
#include "macro.h"
#include "CInputMgr.h"

#include <list>
using namespace std;

// pivot 
// CUnit에 Pivot 기능을 추가
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

		CInputMgr::GetInstance()->Create(m_hWnd);
		CInputMgr::GetInstance()->AddKey("OnFire", VK_SPACE);
		CInputMgr::GetInstance()->AddKey("OnMoveLeft", 'A');
		CInputMgr::GetInstance()->AddKey("OnMoveRight", 'D');

		CInputMgr::GetInstance()->AddKey("OnTest", VK_LCONTROL, 'G');

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);

		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");

		// 만들어질 유닛에 그려질 텍스터를 세팅 
		m_Unit = new CUnit();
		m_Unit->SetTexture(m_Ctexture);
		m_Unit->SetAnchors(0.5f, 0.5f);
		m_Unit->SetPosition(SVector2D(400.0f, 500.0f));

	}

	virtual void OnDestroy() override {
		// TODO : 게임 정리

		if (m_Ctexture != nullptr) {
			delete m_Ctexture;
			m_Ctexture = nullptr;
		}

		SAFE_DELETE(m_Unit);
		/*if (m_Unit != nullptr) {
			delete m_Unit;
			m_Unit = nullptr;
		}*/

		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate() override {

		// input
		if (CInputMgr::GetInstance()->KeyPress("OnMoveLeft")) {
			m_Unit->SetVelocity(SVector2D(-0.01f, 0.0f));
			m_Unit->Update();
		}
		if (CInputMgr::GetInstance()->KeyPress("OnMoveRight")) {
			m_Unit->SetVelocity(SVector2D(0.01f, 0.0f));
			m_Unit->Update();
		}
		if (CInputMgr::GetInstance()->KeyDown("OnFire")) {
			OutputDebugString(L"Skill\n");
			MessageBox(m_hWnd, L"Skill00\n", L"Skill00", MB_OK);
		}
		if (CInputMgr::GetInstance()->KeyDown("OnTest")) {
			OutputDebugString(L"Test..............\n");
		}

		CInputMgr::GetInstance()->Update();

		CAPIEngine::OnUpdate();
		
		// update

		// render
		this->Clear(0.7f, 0.2f, 0.6f);
	
		m_Unit->Render(this);
		
		// 메모리 버퍼에 그리기
		this->Present();
	}

public:
	CUnit* m_Unit = nullptr;
	CTexture* m_Ctexture = nullptr;

	list<CObject*> m_Objects;

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
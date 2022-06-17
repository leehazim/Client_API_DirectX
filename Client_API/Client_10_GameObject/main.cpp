#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObject.h"

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

		WCHAR szTemp[256] = L"";
		wsprintf(szTemp, L"LSHEngine::OnCreate\n");
		OutputDebugString(szTemp);

		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");

		// 만들어질 유닛에 그려질 텍스터를 세팅 
		m_Unit = new CUnit();
		m_Unit->SetTexture(m_Ctexture);
		m_Unit->SetAnchors(0.5f, 0.5f);


		// text
		CObject* pObject = nullptr;
		pObject = new CObject();
		pObject->AddRef();

		CObject* pA = nullptr;
		pA = pObject;
		pA->AddRef();

		if (pA != nullptr) {
			pA->Release();
			pA = nullptr;
		}
		if (pObject != nullptr) {
			pObject->Release();
			pObject = nullptr;
		}
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

		//this->DrawTexture(m_Unit->m_X, m_Unit->m_Y, m_Ctexture);
		
		// 메모리 버퍼에 그리기
		this->Present();
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
#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObject.h"
#include "macro.h"
#include "CInputMgr.h"
#include "CActor.h"
#include "CBullet.h"
#include <vector>

#include <list>
using namespace std;

#pragma comment (lib,"WinAPIEngine.lib")

class LSHEngine
	: public CAPIEngine {
public:
	LSHEngine() {}
	virtual ~LSHEngine() {}

public:
	virtual void OnCreate() override {
		CAPIEngine::OnCreate();

		/*CInputMgr::GetInstance()->Create(m_hWnd);*/
		CInputMgr::GetInstance()->AddKey("OnFire", VK_SPACE);
		CInputMgr::GetInstance()->AddKey("OnMoveLeft", 'A');
		CInputMgr::GetInstance()->AddKey("OnMoveRight", 'D');

		CInputMgr::GetInstance()->AddKey("OnTest", VK_LCONTROL, 'G');

		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
		m_PFActor = CreatePrefab<CActor>(m_Ctexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

		m_pTextBullet = new CTexture();
		m_pTextBullet->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbullet.bmp");
		m_PFBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f)); 

		m_pActor = InstantObject<CActor>(m_PFActor);
		m_pActor->AddRef();

		CBullet* pBullet = nullptr;
		for (int i = 0; i < 10; i++) {
			pBullet = InstantObject<CBullet>(m_PFBullet);
			pBullet->AddRef();

			pBullet->SetIsActive(false);

			m_Bullets.push_back(pBullet);
			pBullet->AddRef();

			m_Objects.push_back(pBullet);
			pBullet->AddRef();

			pBullet->Release();
			pBullet = nullptr;
		}
	}

	virtual void OnDestroy() override {

		vector<CBullet*>::iterator it;
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) {
			DestroyObject(*it);
		}
		m_Bullets.clear();

		list<CObject*>::iterator itl;
		for (itl = m_Objects.begin(); itl != m_Objects.end(); itl++) {
			if ((*itl) != nullptr) {
				(*itl)->Release();
				(*itl) = nullptr;
			}
		}
		m_Objects.clear();

		DestroyObject(m_pActor);
		DeletePrefab(m_PFActor);
		
		SAFE_DELETE(m_Ctexture);

		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate(float deltaTime) override {
		CAPIEngine::OnUpdate(deltaTime);

		CInputMgr::GetInstance()->Update();

		if (CInputMgr::GetInstance()->KeyPress("OnMoveLeft")) {
			m_pActor->SetVelocity(SVector2D(-1.0f, 0.0f) * 200.0f);
			m_pActor->Update(deltaTime);
		}
		if (CInputMgr::GetInstance()->KeyPress("OnMoveRight")) {
			m_pActor->SetVelocity(SVector2D(1.0f, 0.0f) * 200.0f);
			m_pActor->Update(deltaTime);
		}
		if (CInputMgr::GetInstance()->KeyDown("OnFire")) {
			/*OutputDebugString(L"Skill\n");
			MessageBox(m_hWnd, L"Skill00\n", L"Skill00", MB_OK);*/
			m_pActor->DoFire(m_Bullets);

		}

		if (CInputMgr::GetInstance()->KeyDown("OnTest")) {
			OutputDebugString(L"Test..............\n");
		}

		vector<CBullet *>::iterator it;
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) {
			(*it)->Update(deltaTime);
		}

		this->Clear(0.1f, 0.1f, 0.3f);
	
		m_pActor->Render();
		
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) {
			(*it)->Render();
		}

		this->Present();
	}

public:
	CTexture* m_Ctexture = nullptr;
	CTexture* m_pTextBullet = nullptr;

	CActor* m_pActor = nullptr;

	CUnit* m_PFActor = nullptr;
	CUnit* m_PFBullet = nullptr;
	vector<CBullet*> m_Bullets;

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
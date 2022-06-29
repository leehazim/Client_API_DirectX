#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObject.h"
#include "macro.h"
#include "CInputMgr.h"
#include "CActor.h"
#include "CBullet.h"
#include "CEnemy.h"
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

		// �÷��̾� prefab
		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
		m_PFActor = CreatePrefab<CActor>(m_Ctexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));
		
		// źȯ prefab
		m_pTextBullet = new CTexture();
		m_pTextBullet->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbullet.bmp");
		m_PFBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f)); 

		// �� prefab
		m_pTextEnemy = new CTexture();
		m_pTextEnemy->LoadTexture(this->hInst, this->m_hDC, L"resources/bongenemy.bmp");
		m_PFEnemy = CreatePrefab<CEnemy>(m_pTextEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));

		// �÷��̾� ����
		m_pActor = InstantObject<CActor>(m_PFActor);
		m_pActor->AddRef();

		// źȯ ����
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

		m_PFEnemyBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));
		CBullet* pBulletEnemy = nullptr;
		for (int i = 0; i < 10; i++) {
			pBulletEnemy = InstantObject<CBullet>(m_PFEnemyBullet);
			pBulletEnemy->AddRef();

			pBulletEnemy->SetIsActive(false);

			m_EnemyBullet.push_back(pBulletEnemy);
			pBulletEnemy->AddRef();

			m_Objects.push_back(pBulletEnemy);
			pBulletEnemy->AddRef();

			pBulletEnemy->Release();
			pBulletEnemy = nullptr;
		}

		// �� ����
		m_pEnemy = InstantObject<CEnemy>(m_PFEnemy);
		m_pEnemy->AddRef();
		m_pEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
	}

	virtual void OnDestroy() override {

		// �� �ı�
		DestroyObject(m_pEnemy);
		DeletePrefab(m_PFEnemy);

		// �÷��̾� źȯ �ı�
		vector<CBullet*>::iterator it;
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++) {
			DestroyObject(*it);
		}
		m_EnemyBullet.clear();
		// źȯ �ı�
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) {
			DestroyObject(*it);
		}
		m_Bullets.clear();
		DeletePrefab(m_PFBullet);

		list<CObject*>::iterator itl;
		for (itl = m_Objects.begin(); itl != m_Objects.end(); itl++) {
			if ((*itl) != nullptr) {
				(*itl)->Release();
				(*itl) = nullptr;
			}
		}
		m_Objects.clear();

		// �÷��̾� �ı�
		DestroyObject(m_pActor);
		DeletePrefab(m_PFActor);
		
		SAFE_DELETE(m_pTextEnemy);
		SAFE_DELETE(m_pTextBullet);
		SAFE_DELETE(m_Ctexture);
		
		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate(float deltaTime) override {
		CAPIEngine::OnUpdate(deltaTime);

		CInputMgr::GetInstance()->Update();

		// ������Ʈ ��Ʈ
		if (CInputMgr::GetInstance()->KeyPress("OnMoveLeft")) {
			m_pActor->SetVelocity(SVector2D(-1.0f, 0.0f) * 200.0f);
			m_pActor->Update(deltaTime);
		}
		if (CInputMgr::GetInstance()->KeyPress("OnMoveRight")) {
			m_pActor->SetVelocity(SVector2D(1.0f, 0.0f) * 200.0f);
			m_pActor->Update(deltaTime);
		}
		if (CInputMgr::GetInstance()->KeyDown("OnFire")) {
			m_pActor->DoFire(m_Bullets);
		}

		// �ֱ������� źȯ �߻�
		float timer = 2.0f;
		if (m_pEnemy->m_TimeTick >= timer) {
			m_pEnemy->DoFire(m_EnemyBullet);
			
			float diff = m_pEnemy->m_TimeTick - timer;
			m_pEnemy->m_TimeTick = diff;
		}
		else {
			m_pEnemy->m_TimeTick = m_pEnemy->m_TimeTick + deltaTime;
		}

		// źȯ 
		vector<CBullet*>::iterator it;
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) 
			(*it)->Update(deltaTime);
		
		// ��, ��źȯ ������Ʈ
		m_pEnemy->Update(deltaTime);
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++) 
			(*it)->Update(deltaTime);
		
		// ������ ��Ʈ
		this->Clear(0.0f, 0.0f, 0.0f);
	
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++)
			(*it)->Render(); 
		m_pActor->Render();

		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++)
			(*it)->Render();
		m_pEnemy->Render();

		this->Present();
	}

public:
	CTexture* m_Ctexture = nullptr;			// �÷��̾� prefab�� �ؽ���
	CUnit* m_PFActor = nullptr;
	CActor* m_pActor = nullptr;

	CTexture* m_pTextBullet = nullptr;		// �÷��̾� �Ѿ� prefab�� �ؽ�ó
	CUnit* m_PFBullet = nullptr;
	vector<CBullet*> m_Bullets;

	CTexture* m_pTextEnemy = nullptr;		// �� prefab�� �ؽ�ó
	CUnit* m_PFEnemy = nullptr;
	CEnemy* m_pEnemy = nullptr;
	vector<CBullet*> m_EnemyBullet;
	CUnit* m_PFEnemyBullet = nullptr;

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
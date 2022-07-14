#include "CAPIEngine.h"
#include "CUnit.h"
#include "CTexture.h"
#include "CObject.h"
#include "macro.h"
#include "CInputMgr.h"
#include "CActor.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CCollisionMgr.h"
#include "CAnimator.h"
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

		/*CCollisionMgr::GetInstance();*/

		/*CInputMgr::GetInstance()->Create(m_hWnd);*/
		CInputMgr::GetInstance()->AddKey("OnFire", VK_SPACE);
		CInputMgr::GetInstance()->AddKey("OnMoveLeft", 'A');
		CInputMgr::GetInstance()->AddKey("OnMoveRight", 'D');

		// 플레이어 prefab
		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
		m_PFActor = CreatePrefab<CActor>(m_Ctexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));
		
		// 탄환 prefab
		m_pTextBullet = new CTexture();
		m_pTextBullet->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbullet.bmp");
		m_PFBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f)); 

		// 적 prefab
		m_pTextEnemy = new CTexture();
		m_pTextEnemy->LoadTexture(this->hInst, this->m_hDC, L"resources/bongenemy.bmp");
		m_PFEnemy = CreatePrefab<CEnemy>(m_pTextEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));

		// 플레이어 생성
		m_pActor = InstantObject<CActor>(m_PFActor);
		m_pActor->AddRef();

		CAnimator* pAnimActor = m_pActor->CreateAnimator("AnimActor", this);
		pAnimActor->AddAniSeq("ani_idle_actor", 1.0f, 2, L"resources/bongbong");

		// 탄환 생성
		CBullet* pBullet = nullptr;
		for (int i = 0; i < 10; i++) {
			pBullet = InstantObject<CBullet>(m_PFBullet);
			pBullet->AddRef();

			pBullet->SetIsActive(false);

			pBullet->SetTag("tagActorBullet");
			m_Bullets.push_back(pBullet);
			pBullet->AddRef();
			

			m_Objects.push_back(pBullet);
			pBullet->AddRef();

			pBullet->Release();
			pBullet = nullptr;
		}
		// 적 생성
		m_pEnemy = InstantObject<CEnemy>(m_PFEnemy);
		m_pEnemy->AddRef();
		m_pEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);

		// 적(조준탄발사) 생성
		//m_pEnemyAimed = InstantObject<CEnemy>(m_PFEnemy);
		//m_pEnemyAimed->AddRef();
		//m_pEnemyAimed->SetVelocity(SVector2D(+1.0f, 0.0f) * 50.0f);
		//m_pEnemyAimed->SetPosition(SVector2D(400.0f, 150.0f));

		//// 적(원형 탄) 생성
		//m_pEnemyCircle = InstantObject<CEnemy>(m_PFEnemy);
		//m_pEnemyCircle->AddRef();
		//m_pEnemyCircle->SetVelocity(SVector2D(1.0f, 0.0f) * 25.0f);
		//m_pEnemyCircle->SetPosition(SVector2D(400.0f, 200.0f));

		// 적 탄환 생성
		m_PFEnemyBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));
		CBullet* pBulletEnemy = nullptr;
		for (int i = 0; i < 16; i++) {
			pBulletEnemy = InstantObject<CBullet>(m_PFEnemyBullet);
			pBulletEnemy->AddRef();

			pBulletEnemy->SetIsActive(false);

			pBulletEnemy->SetTag("tagEnemyBullet");
			m_EnemyBullet.push_back(pBulletEnemy);
			pBulletEnemy->AddRef();

			m_Objects.push_back(pBulletEnemy);
			pBulletEnemy->AddRef();

			pBulletEnemy->Release();
			pBulletEnemy = nullptr;
		}

		// 간략하게 하기 위해서 적 오브젝트를 하나만 사용해서 충돌 적용이 가능한지 확인하자
		// 조준탄 생성
		//for (int i = 0; i < 10; i++) {
		//	pBulletEnemy = InstantObject<CBullet>(m_PFEnemyBullet);
		//	pBulletEnemy->AddRef();

		//	pBulletEnemy->SetIsActive(false);

		//	m_AimedBullet.push_back(pBulletEnemy);
		//	pBulletEnemy->AddRef();

		//	m_Objects.push_back(pBulletEnemy);
		//	pBulletEnemy->AddRef();

		//	pBulletEnemy->Release();
		//	pBulletEnemy = nullptr;
		//}
		//// 원형탄 생성
		//for (int i = 0; i < 16; i++) {
		//	pBulletEnemy = InstantObject<CBullet>(m_PFEnemyBullet);
		//	pBulletEnemy->AddRef();
		//	
		//	pBulletEnemy->SetIsActive(false);

		//	m_CircleBullet.push_back(pBulletEnemy);
		//	pBulletEnemy->AddRef();

		//	m_Objects.push_back(pBulletEnemy);
		//	pBulletEnemy->AddRef();
		//	
		//	pBulletEnemy->Release();
		//	pBulletEnemy = nullptr;
		//}

	
	}

	virtual void OnDestroy() override {

		

		// 적탄환 파괴
		vector<CBullet*>::iterator it;
		/*for (it = m_CircleBullet.begin(); it != m_CircleBullet.end(); it++) {
			DestroyObject(*it);
		}
		m_CircleBullet.clear();
		for (it = m_AimedBullet.begin(); it != m_AimedBullet.end(); it++) {
			DestroyObject(*it);
		}
		m_AimedBullet.clear();*/
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++) {
			DestroyObject(*it);
		}
		m_EnemyBullet.clear();

		//DestroyObject(m_pEnemyCircle);
		//// 적(조준탄발사) 파괴
		//DestroyObject(m_pEnemyAimed);
		// 적 파괴
		DestroyObject(m_pEnemy);
		DeletePrefab(m_PFEnemy);

		// 탄환 파괴
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

		// 플레이어 파괴
		DestroyObject(m_pActor);
		DeletePrefab(m_PFActor);
		
		SAFE_DELETE(m_pTextEnemy);
		SAFE_DELETE(m_pTextBullet);
		SAFE_DELETE(m_Ctexture);
		
		/*CCollisionMgr::ReleaseInstance();*/
		//CInputMgr::ReleaseInstance();
		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate(float deltaTime) override {
		CAPIEngine::OnUpdate(deltaTime);


		// collision circle
		/*CCollisionMgr::GetInstance()->Update(deltaTime);*/

		// 적 vs 주인공 탄환 오브젝트의 충돌 확인
		//vector<CBullet*>::iterator its;
		//for (its = m_Bullets.begin(); its != m_Bullets.end(); its++) {
		//	if ((*its)->GetIsActive()) {
		//		if (m_pEnemy->GetIsActive()) {
		//			bool isCollision = false;
		//			/*isCollision = (*its)->GetCollider()->DoCollision(m_pEnemy->GetCollider(), 1);*/
		//			isCollision = (*its)->GetCollider()->DoCollisionby(m_pEnemy);
		//			if (isCollision) {
		//				OutputDebugString(L"Collision!!!!!!!!!!!!!!!!!!!!!\n");
		//				(*its)->SetIsActive(false);
		//				m_pEnemy->SetIsActive(false);
		//				break;
		//			}
		//		}
		//		else { break; }
		//	}
		//	else { break; }
		//}
		


		CInputMgr::GetInstance()->Update();

		// 업데이트 파트
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

		// 주기적으로 탄환 발사

		/*float timer = 3.0f;
		if (m_pEnemyCircle->m_TimeTick >= timer) {
			m_pEnemyCircle->DoFireCircle(m_CircleBullet);

			float diff = m_pEnemyCircle->m_TimeTick - timer;
			m_pEnemyCircle->m_TimeTick = diff;
		}
		else {
			m_pEnemyCircle->m_TimeTick = m_pEnemyCircle->m_TimeTick + deltaTime;
		}


		float timer2 = 2.5f;
		if (m_pEnemyAimed->m_TimeTick >= timer2) {
			m_pEnemyAimed->DoFireAimed(m_AimedBullet, m_pActor);

			float diff = m_pEnemyAimed->m_TimeTick - timer2;
			m_pEnemyAimed->m_TimeTick = diff;
		}
		else {
			m_pEnemyAimed->m_TimeTick = m_pEnemyAimed->m_TimeTick + deltaTime;
		}*/
		float timer = 2.0f;
		if (m_pEnemy->m_TimeTick >= timer) {
			m_pEnemy->DoFireCircle(m_EnemyBullet);
			
			float diff = m_pEnemy->m_TimeTick - timer;
			m_pEnemy->m_TimeTick = diff;
		}
		else {
			m_pEnemy->m_TimeTick = m_pEnemy->m_TimeTick + deltaTime;
		}

		// 탄환 
		vector<CBullet*>::iterator it;
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) 
			(*it)->Update(deltaTime);
		
		// 적, 적탄환 업데이트
		m_pEnemy->Update(deltaTime);
	/*	m_pEnemyAimed->Update(deltaTime);
		m_pEnemyCircle->Update(deltaTime);*/
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++) 
			(*it)->Update(deltaTime);
		/*for (it = m_AimedBullet.begin(); it != m_AimedBullet.end(); it++)
			(*it)->Update(deltaTime);
		for (it = m_CircleBullet.begin(); it != m_CircleBullet.end(); it++) 
			(*it)->Update(deltaTime);*/
		
		// 렌더링 파트
		this->Clear(1.0f, 1.0f, 1.0f);
	
		m_pActor->Render();
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++)
			(*it)->Render(); 

		m_pEnemy->Render();
		/*m_pEnemyAimed->Render();
		m_pEnemyCircle->Render();*/
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++)
			(*it)->Render();
		/*for (it = m_AimedBullet.begin(); it != m_AimedBullet.end(); it++)
			(*it)->Render();
		for (it = m_CircleBullet.begin(); it != m_CircleBullet.end(); it++)
			(*it)->Render();*/

		

		this->Present();
	}

public:
	CTexture* m_Ctexture = nullptr;			// 플레이어 prefab용 텍스쳐
	CUnit* m_PFActor = nullptr;
	CActor* m_pActor = nullptr;

	CTexture* m_pTextBullet = nullptr;		// 플레이어 총알 prefab용 텍스처
	CUnit* m_PFBullet = nullptr;
	vector<CBullet*> m_Bullets;

	CTexture* m_pTextEnemy = nullptr;		// 적 prefab용 텍스처
	CUnit* m_PFEnemy = nullptr;
	CEnemy* m_pEnemy = nullptr;
	vector<CBullet*> m_EnemyBullet;
	CUnit* m_PFEnemyBullet = nullptr;

	/*CEnemy* m_pEnemyAimed = nullptr;
	vector<CBullet*> m_AimedBullet;

	CEnemy* m_pEnemyCircle = nullptr;
	vector<CBullet*> m_CircleBullet;*/

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
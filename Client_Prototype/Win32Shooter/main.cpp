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

		CInputMgr::GetInstance()->AddKey("OnTest_1", VK_CONTROL, 'H');
		CInputMgr::GetInstance()->AddKey("OnTest_0", VK_CONTROL, 'G');

		// �÷��̾� prefab
		m_Ctexture = new CTexture();
		m_Ctexture->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbong_0.bmp");
		m_PFActor = CreatePrefab<CActor>(m_Ctexture, 0.5f, 0.5f, SVector2D(400.0f, 500.0f));

		// ������ �ִϸ����� ���� ����Ǵ� ������Ʈ���� ��� �ִϸ����͸� �� �� �ް� ��
		CAnimator* pAnimActor = m_PFActor->CreateAnimator("AnimActor", this);
		pAnimActor->SetOwnerObject(m_PFActor);
		pAnimActor->AddAniSeq("ani_idle_actor", 1.0f, 2, L"resources/bongbong");
		pAnimActor->AddAniSeq("ani_super_actor", 1.0f, 1, L"resources/bongbong_super");
		m_PFActor->GetAnimator()->SetKey("ani_idle_actor");

		// źȯ prefab
		m_pTextBullet = new CTexture();
		m_pTextBullet->LoadTexture(this->hInst, this->m_hDC, L"resources/bongbullet.bmp");
		m_PFBullet = CreatePrefab<CBullet>(m_pTextBullet, 0.5f, 0.5f, SVector2D(400.0f, 500.0f)); 

		CAnimator* pAniBullet = m_PFBullet->CreateAnimator("AnimBullet", this);
		pAniBullet->SetOwnerObject(m_PFBullet);
		pAniBullet->AddAniSeq("ani_idle_bullet", 0.01f, 4 * 8, L"resources/explosionFull", ANI_INFO::LOOP, ANI_SO::SHEET_FILE, 4, 8);
		m_PFBullet->SetDefaultAniSeq("ani_idle_bullet");

		// �� prefab
		m_pTextEnemy = new CTexture();
		/*m_pTextEnemy->LoadTexture(this->hInst, this->m_hDC, L"resources/bongenemy.bmp");*/
		m_pTextEnemy->LoadTexture(this->hInst, this->m_hDC, L"resources/paladin_idle_0.bmp");
		m_PFEnemy = CreatePrefab<CEnemy>(m_pTextEnemy, 0.5f, 0.5f, SVector2D(400.0f, 100.0f));

		//TODO: Test
		CAnimator* pAnimEnemy = m_PFEnemy->CreateAnimator("AnimEnemy", this);
		pAnimEnemy->SetOwnerObject(m_PFEnemy);
		pAnimEnemy->AddAniSeq("ani_idle_enemy", 0.05f, 7, L"resources/paladin_idle");
		pAnimEnemy->AddAniSeq("ani_attack_enemy", 0.08f, 10, L"resources/paladin_attack", ANI_INFO::ONCE);
		pAnimEnemy->SetDefaultAniSeq("ani_idle_enemy");
		
		// �÷��̾� ����
		m_pActor = InstantObject<CActor>(m_PFActor);
		m_pActor->AddRef();

		// ���Ϳ� �ٷ� �����ϴ� ��
		/*CAnimator* pAnimActor = m_pActor->CreateAnimator("AnimActor", this);
		pAnimActor->AddAniSeq("ani_idle_actor", 1.0f, 2, L"resources/bongbong");*/

		// źȯ ����
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
		// �� ����
		m_pEnemy = InstantObject<CEnemy>(m_PFEnemy);
		m_pEnemy->AddRef();
		m_pEnemy->SetVelocity(SVector2D(+1.0f, 0.0f) * 100.0f);
		

		// ��(����ź�߻�) ����
		//m_pEnemyAimed = InstantObject<CEnemy>(m_PFEnemy);
		//m_pEnemyAimed->AddRef();
		//m_pEnemyAimed->SetVelocity(SVector2D(+1.0f, 0.0f) * 50.0f);
		//m_pEnemyAimed->SetPosition(SVector2D(400.0f, 150.0f));

		//// ��(���� ź) ����
		//m_pEnemyCircle = InstantObject<CEnemy>(m_PFEnemy);
		//m_pEnemyCircle->AddRef();
		//m_pEnemyCircle->SetVelocity(SVector2D(1.0f, 0.0f) * 25.0f);
		//m_pEnemyCircle->SetPosition(SVector2D(400.0f, 200.0f));

		// �� źȯ ����
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

		// �����ϰ� �ϱ� ���ؼ� �� ������Ʈ�� �ϳ��� ����ؼ� �浹 ������ �������� Ȯ������
		// ����ź ����
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
		//// ����ź ����
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

		// ��źȯ �ı�
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
		//// ��(����ź�߻�) �ı�
		//DestroyObject(m_pEnemyAimed);
		// �� �ı�
		DestroyObject(m_pEnemy);
		DeletePrefab(m_PFEnemy);

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
		
		/*CCollisionMgr::ReleaseInstance();*/
		//CInputMgr::ReleaseInstance();
		CAPIEngine::OnDestroy();
	}

	virtual void OnUpdate(float deltaTime) override {
		CAPIEngine::OnUpdate(deltaTime);


		// collision circle
		/*CCollisionMgr::GetInstance()->Update(deltaTime);*/

		// �� vs ���ΰ� źȯ ������Ʈ�� �浹 Ȯ��
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
	
		// test
		if (CInputMgr::GetInstance()->KeyDown("OnTest_1")) {
			m_pActor->GetAnimator()->SetKey("ani_idle_actor");
		}
		if (CInputMgr::GetInstance()->KeyDown("OnTest_0")) {
			m_pActor->GetAnimator()->SetKey("ani_super_actor");
		}
		// �ֱ������� źȯ �߻�

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
		else {d
			m_pEnemyAimed->m_TimeTick = m_pEnemyAimed->m_TimeTick + deltaTime;
		}*/
		float timer = 2.0f;
		if (m_pEnemy->m_TimeTick >= timer) {
			m_pEnemy->GetAnimator()->PlayAni("ani_attack_enemy");
			isFire = true;
			//m_pEnemy->DoFire(m_EnemyBullet);
			float diff = m_pEnemy->m_TimeTick - timer;
			m_pEnemy->m_TimeTick = diff;
		}
		else {
			m_pEnemy->m_TimeTick = m_pEnemy->m_TimeTick + deltaTime;
		}
		if (m_pEnemy->GetAnimator()->GetKey() == "ani_attack_enemy") {
			if (isFire && m_pEnemy->GetAnimator()->GetAniSeq()->GetCurIndex() == 5) {
				m_pEnemy->DoFireCircle(m_EnemyBullet);
				isFire = false;
			}
		}

		// źȯ 
		vector<CBullet*>::iterator it;
		for (it = m_Bullets.begin(); it != m_Bullets.end(); it++) 
			(*it)->Update(deltaTime);
		
		// ��, ��źȯ ������Ʈ
		m_pEnemy->Update(deltaTime);
	  /*m_pEnemyAimed->Update(deltaTime);
		m_pEnemyCircle->Update(deltaTime);*/
		for (it = m_EnemyBullet.begin(); it != m_EnemyBullet.end(); it++) 
			(*it)->Update(deltaTime);
		/*for (it = m_AimedBullet.begin(); it != m_AimedBullet.end(); it++)
			(*it)->Update(deltaTime);
		for (it = m_CircleBullet.begin(); it != m_CircleBullet.end(); it++) 
			(*it)->Update(deltaTime);*/
		
		// ������ ��Ʈ
		this->Clear(0.3f, 0.2f, 0.8f);
	
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

	/*CEnemy* m_pEnemyAimed = nullptr;
	vector<CBullet*> m_AimedBullet;

	CEnemy* m_pEnemyCircle = nullptr;
	vector<CBullet*> m_CircleBullet;*/

	list<CObject*> m_Objects;
	bool isFire = false;

private:
	LSHEngine(const LSHEngine& other) = delete;
	LSHEngine& operator=(const LSHEngine& other) = delete;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	
	LSHEngine Game;
	Game.Create(hInstance, nCmdShow);
	MSG msg = Game.Run();

	return (int)msg.wParam;
}